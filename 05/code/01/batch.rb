#!/usr/bin/env ruby
# kate: remove-trailing-space on; replace-trailing-space-save on; indent-width 2; indent-mode ruby; syntax ruby; space-indent on;

# http://codeidol.com/other/rubyckbk/Numbers/Finding-Mean,-Median,-and-Mode/
class Array
  def mean
    self.inject(0) { |sum, x| sum += x } / self.size.to_f
  end

  def median already_sorted = false
    return nil if self.empty?
    self.sort! unless already_sorted
    m_pos = self.size / 2
    return self.size % 2 == 1 ? self[m_pos] : self[m_pos-1..m_pos].mean
  end
end


repitions = 3

File.open('../data/data1.dat', 'w') do |file|
  file.puts "#N S mpicc 1 2 3 4"
  nn = 10**7
  ss = 1
  r = 100
  line = "#{nn} #{ss}"
  compiler = 'mpicc'
  system 'rm -f *.o a.out'
  system "#{compiler} -c daxpy.c empty.c > /dev/null 2>&1"
  system "#{compiler} steuerung.c daxpy.o empty.o wall_time.c > /dev/null 2>&1"

  (1..4).each do |nprocesses|
    puts "\ncurrent config: #{compiler} N=#{nn} S=#{ss} r=#{r} Nprocesses=#{nprocesses}"
    values = []
    10.times do |i|
      print "#{i} "
      cmd = "mpirun -n #{nprocesses} a.out #{nn} #{r} #{ss}"
      out = `#{cmd}`
      match = out.match(/Rechenleistung :\s+(.+)\s+MFlop\/s/)
      if match
        values << match[1].to_f
      else
        $stderr.puts "Fehler bei #{cmd}"
      end
    end
    line += " %6.1f" % values.median if values.any?
  end
  file.puts line
end