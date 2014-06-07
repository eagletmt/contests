xml.instruct!
xml.feed xmlns: 'http://www.w3.org/2005/Atom' do
  blog_url = URI.join('https://eagletmt.github.io/', http_prefix)

  xml.id blog_url
  xml.title data.config.title
  xml.link href: blog_url
  xml.link href: URI.join(blog_url, current_page.path), rel: 'self'
  xml.author do
    xml.name data.config.author
  end
  unless blog.articles.empty?
    xml.updated blog.articles.first.date.to_time.iso8601
  end

  def git_authored_time(article)
    cmd = ['git', 'log', '-1', '--format=%at', '--', article.source_file]
    Time.at(IO.popen(cmd, 'r', &:read).chomp.to_i)
  end

  blog.articles[0 ... 20].each do |article|
    xml.entry do
      article_url = URI.join(blog_url, article.url)

      xml.title article.title
      xml.link href: article_url, rel: 'alternate'
      xml.id article_url
      xml.published article.date.to_time.iso8601
      xml.updated git_authored_time(article).iso8601
      xml.author do
        xml.name data.config.author
      end
      xml.content article.body, type: 'html'
    end
  end
end
