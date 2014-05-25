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

namespace :images do
  desc 'Generate SVG from dot'
  task :generate do
    Dir.glob('source/images/**/*.dot').each do |dot|
      dot_path = Pathname.new(dot)
      svg_path = dot_path.sub_ext('.svg')
      sh 'dot', '-Tsvg', '-o', svg_path.to_s, dot_path.to_s
    end
  end
end
