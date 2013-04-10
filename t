[1mdiff --git a/blotter/kbest.rb b/blotter/kbest.rb[m
[1mindex e16c35b..b80d3fa 100755[m
[1m--- a/blotter/kbest.rb[m
[1m+++ b/blotter/kbest.rb[m
[36m@@ -3,9 +3,10 @@[m
 require 'trollop'[m
 require 'open3'[m
 require 'set'[m
[31m-require 'pry'[m
[32m+[m[32mrequire 'fileutils'[m
[32m+[m[32m# require 'pry'[m
 [m
[31m-opts = Trollop::options do[m
[32m+[m[32m$opts = Trollop::options do[m
   opt :k,       'number of results to consider',                  default: 3[m
   opt :diff,    '% of difference between the k selected results', default: 0.05[m
   opt :min,     'minimum number of executions',                   default: 1,        short: :m[m
[36m@@ -29,7 +30,7 @@[m [mclass Execution[m
   def <=>(other)[m
     ret = @value <=> other.value[m
     return @thread.pid <=> other.thread.pid if ret.zero?[m
[31m-    return  ret unless opts[:reverse][m
[32m+[m[32m    return  ret unless $opts[:reverse][m
     return -ret[m
   end[m
 end[m
[36m@@ -44,7 +45,7 @@[m [mend[m
 [m
 [m
 execs = SortedSet.new[m
[31m-k     = opts[:k][m
[32m+[m[32mk     = $opts[:k][m
 [m
 begin[m
   puts "    run #[#{execs.size}]"[m
[36m@@ -54,11 +55,11 @@[m [mbegin[m
   values = execs.to_a[0..k].map(&:value)[m
   # results are ordered, so the last diff is enough to check if we have k good results[m
   diff = (values.last - values.first) / values.first[m
[31m-end until done?(execs.size, values.size, diff, opts)[m
[32m+[m[32mend until done?(execs.size, values.size, diff, $opts)[m
 [m
 final = execs.to_a[0..k][m
 [m
[31m-out_root = opts[:out][m
[32m+[m[32mout_root = $opts[:out][m
 FileUtils.mkdir_p out_root[m
 times_output = File.open("#{out_root}/kbest_times.csv", 'w')[m
 final.each_with_index do |exec, i|[m
[36m@@ -72,3 +73,4 @@[m [mfinal.each_with_index do |exec, i|[m
 end[m
 [m
 times_output.close[m
[41m+[m
