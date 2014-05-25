require 'slim'
require 'liquid'
require 'pygments'

class IncludeCodeTag < Liquid::Tag
  def initialize(tag_name, markup, tokens)
    super
    markup = markup.strip
    if m = markup.match(/\Alang:(\S+)\s+(.+)\z/)
      @language = m[1]
      @path = m[2]
    else
      raise "Markup syntax error: #{markup}"
    end
  end

  def render(context)
    path = "source/code/#{@path}"
    %Q{<pre>#{Pygments.highlight(File.read(path), lexer: @language, options: { linenos: 'inline' })}</pre>}
  end
end

Liquid::Template.register_tag('include_code', IncludeCodeTag)

helpers do
  def find_next_article(blog_article)
    index = blog.articles.find_index(blog_article)
    if index > 0
      blog.articles[index-1]
    end
  end

  def find_prev_article(blog_article)
    index = blog.articles.find_index(blog_article)
    blog.articles[index+1]
  end
end

set :css_dir, 'stylesheets'
#set :js_dir, 'javascripts'
#set :images_dir, 'images'

set :markdown_engine, :redcarpet
set :http_prefix, '/contests'

configure :build do
  activate :asset_hash
end

activate :blog do |blog|
  blog.permalink = 'blog/{title}.html'
  blog.paginate = true
  blog.page_link = 'blog/page/{num}'
  blog.per_page = 20
  blog.summary_generator = lambda do |blog_article, rendered, length, ellipsis|
    "#{blog_article.date.strftime('%F')} #{blog_article.title}"
  end
end

activate :livereload
activate :directory_indexes
