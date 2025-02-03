package com.example.articles.repository

import com.example.articles.domain.Article
import com.example.articles.utils.demoArticles

class InMemoryRepository {
    private val articles: MutableList<Article> = demoArticles.toMutableList()
    fun addArticle(article: Article) {
        this.articles.add(article)
    }

    fun getArticles(): List<Article> {
        return this.articles.toList()
    }

    fun updateArticle(article: Article) {
        this.articles.forEachIndexed { index, currentArticle ->
            currentArticle.takeIf { it.articleId == article.articleId }?.let {
                this.articles[index] = it.copy(
                    articleId = it.articleId,
                    title = article.title,
                    context = article.context,
                    author = article.author,
                    date = article.date,
                    category = article.category
                )
            }
        }
    }

    fun deleteArticle(articleId: String) {
        this.articles.removeIf { it.articleId == articleId }
    }
}