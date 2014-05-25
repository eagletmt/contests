namespace :pygments do
  desc 'Generate CSS file for pygments'
  task :css do
    require 'pygments'
    path = 'source/stylesheets/pygments.css'
    opts = {}
    if ENV['STYLE']
      opts[:style] = ENV['STYLE']
    end

    css = Pygments.css('.highlight', opts)
    File.open(path, 'w') do |f|
      css.each_line do |line|
        line.chomp!
        # Skip background
        unless line =~ /\.highlight .+background:/
          f.puts line
        end
      end
    end
  end
end
