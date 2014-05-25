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
    link = "/contests/code/#{@path}"
    %Q{<pre>#{Pygments.highlight(File.read(path), lexer: @language, options: { linenos: 'inline' })}</pre><a href="#{link}">#{@path}</a>}
  end
end

Liquid::Template.register_tag('include_code', IncludeCodeTag)

helpers do
  def simple_link_to(link)
    link_to link, link
  end

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
set :images_dir, 'images'

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
end

activate :livereload
activate :directory_indexes
