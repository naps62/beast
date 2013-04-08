#!/usr/bin/env ruby

require 'trollop'
require 'open3'
require 'set'
require 'pry'

opts = Trollop::options do
  opt :k,       'number of results to consider',                  default: 3
  opt :diff,    '% of difference between the k selected results', default: 0.05
  opt :min,     'minimum number of executions',                   default: 1,        short: :m
  opt :max,     'maximum number of executions',                   default: 20,       short: :M
  opt :reverse, 'are we looking for the highest instead?',        default: false,    short: :r
  opt :out,     'output directory',                               default: 'kbest/', short: :o
end

command = ARGV.join ' '

class Execution
  attr_accessor :value, :out, :err, :thread

  def initialize(command)
    stdin, out, err, @thread = Open3.popen3(command)
    @out = out.readlines
    @err = err.readlines
    @value = @err.last.to_f
  end

  def <=>(other)
    ret = @value <=> other.value
    return @thread.pid <=> other.thread.pid if ret.zero?
    return  ret unless opts[:reverse]
    return -ret
  end
end


def done?(size, diff, params)
  return false if params[:min] > 0 && size <  params[:min] # at least #{min} runs made
  return true  if params[:max] > 0 && size >= params[:max] # at most  #{max} runs made
  return true  if size >= params[:k]
  return false
end


execs = SortedSet.new
k     = opts[:k]

begin
  # call the program
  execs.add(Execution.new(command))
  # only the value of the first k results is relevant
  values = execs.to_a[0..k].map(&:value)
  # results are ordered, so the last diff is enough to check if we have k good results
  diff = (values.last - values.first) / values.first
end until done?(values.size, diff, opts)

final = execs.to_a[0..k]

out_root = opts[:out]
FileUtils.mkdir out_root
times_output = File.open("#{out_root}/times", 'w')
final.each_with_index do |exec, i|
  times_output << "#{i}, #{exec.value}\n"
  single_exec_output = File.open("#{out_root}/#{i}.csv", 'w')
  single_exec_output << exec.out.join
  single_exec_output.close
end

times_output.close

binding.pry
