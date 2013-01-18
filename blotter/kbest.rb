#/usr/bin/env ruby

require 'trollop'
require 'open3'
require 'set'

opts = Trollop::options do
  opt :k,       'number of results to consider',                  default: 5
  opt :diff,    '% of difference between the k selected results', default: 0.10
  opt :min,     'minimum number of executions',                   default: 1,     short: :m
  opt :max,     'maximum number of executions',                   default: 20,    short: :M
  opt :reverse, 'are we looking for the highest instead?',        default: false, short: :r
end

command = ARGV.join ' '

class Execution
  attr_accessor :value, :out, :err

  def initialize(command)
    stdin, @out, @err = Open3.popen3(command)
    @value = @out.split.last.to_f
  end

  def <=>(other)
    return @value <=> other.value unless opts[:reverse]
    return other.value <=> @value
  end
end

def done?(size, diff, params)
  return false if params[:min] > 0 && size <  params[:min] # at least #{min} runs made
  return true  if params[:max] > 0 && size >= params[:max] # at most  #{max} runs made
  return true  if k >= params[:k]
  return false
end


execs = SortedSet.new
done  = false
k     = opts[:k]

loop
  # call the program
  execs.add(Execution.new(command))
  # only the value of the first k results is relevant
  values = execs[0..k].map(&:value)
  # results are ordered, so the last diff is enough to check if we have k good results
  diff = (values.last - values.first) / values.first
until done?(values.size, diff, opts)

binding.pry
