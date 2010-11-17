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


repitions = { 5 => 2, 6 => 1, 7 => 0 }
repitions.default = 3

File.open('../data/data.dat', 'w') do |file|
  file.puts "#N S gcc gcc(0) gcc(3) icc icc(0) icc(3) pgcc pgcc(0) pgcc(3)"
  (2..7).each do |n|
    nn = 10**n
    (0..6).each do |s|
      ss = 2**s
      line = "#{nn} #{ss}"
      ['gcc', 'icc', 'pgcc'].each do |compiler|
        ['', ' -O0', ' -O3'].each do |optimization|
          r = 10**repitions[n]
          puts "\ncurrent config: #{compiler}#{optimization} N=#{nn} S=#{ss} r=#{r}"
          system 'rm -f *.o a.out'
          system "#{compiler}#{optimization} -c skalar.c empty.c > /dev/null 2>&1"
          system "#{compiler}#{optimization} skalarprodukt4.c skalar.o empty.o wall_time.c > /dev/null 2>&1"
          values = []
          10.times do |i|
            print "#{i} "
            out = `./a.out #{nn} #{r} #{ss}`
            match = out.match(/Rechenleistung :\s+(.+)\s+MFlop\/s/)
            if match
              values << match[1].to_f
            else
              puts out
              gets
            end
          end
          line += " %6.1f" % values.median
        end
      end
      file.puts line
    end
  end
end