package com.example.articles.viewmodels

import androidx.lifecycle.ViewModel
import com.example.articles.domain.Article
import com.example.articles.domain.ArticleCategory
import com.example.articles.repository.InMemoryRepository
import dagger.hilt.android.lifecycle.HiltViewModel
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import java.text.SimpleDateFormat
import java.util.Date
import java.util.Locale
import java.util.UUID
import javax.inject.Inject

@HiltViewModel
class ArticlesViewModel @Inject constructor(
    private val articlesRepository: InMemoryRepository
) : ViewModel() {
    private val _articlesData = MutableStateFlow(ArticlesViewModelData())
    val articlesData: StateFlow<ArticlesViewModelData> = _articlesData.asStateFlow()

    init {
        _articlesData.value = ArticlesViewModelData(
            this.articlesRepository.getArticles(), this.articlesRepository.getArticles()
        )
    }

    private fun convertCategoryToString(category: String): ArticleCategory {
        when (category) {
            "Technology" -> return ArticleCategory.TECHNOLOGY
            "Science" -> return ArticleCategory.SCIENCE
            "Business" -> return ArticleCategory.BUSINESS
            "Health" -> return ArticleCategory.HEALTH
            "Sports" -> return ArticleCategory.SPORTS
            "Education" -> return ArticleCategory.EDUCATION
            "Travel" -> return ArticleCategory.TRAVEL
            "Food" -> return ArticleCategory.FOOD
        }
        throw Exception("Invalid category")
    }

    private fun createArticle(
        articleId: String? = null,
        title: String,
        context: String,
        author: String,
        date: String,
        category: String
    ): Article {
        val postingDate = try {
            SimpleDateFormat("dd/MM/yyyy", Locale.getDefault()).parse(date)
        } catch (e: Exception) {
            e.printStackTrace() // Add this line to print the error if parsing fails
            Date(System.currentTimeMillis()) // Fallback to current date
        }


        return Article(
            articleId = articleId ?: UUID.randomUUID().toString(),
            title = title,
            context = context,
            author = author,
            date = postingDate,
            category = convertCategoryToString(category)
        )
    }

    fun addArticle(
        title: String, context: String, author: String, date: String, category: String
    ) {
        val articleToAdd = this.createArticle(
            title = title,
            context = context,
            author = author,
            date = date,
            category = category
        )

        _articlesData.value = _articlesData.value.copy(
            articles = _articlesData.value.articles + articleToAdd,
            filteredArticles = _articlesData.value.articles + articleToAdd,
            filterKey = ""
        )

        articlesRepository.addArticle(articleToAdd)
    }

    fun updateArticle(
        articleId: String, title: String, context: String, author: String, date: String, category: String
    ) {
        val articleToUpdate = this.createArticle(
            articleId = articleId,
            title = title,
            context = context,
            author = author,
            date = date,
            category = category
        )

        val articles = this._articlesData.value.articles.map { if (it.articleId == articleId) articleToUpdate else it }

        _articlesData.value = _articlesData.value.copy(articles = articles, filteredArticles = articles, filterKey = "")

        this.articlesRepository.updateArticle(articleToUpdate)
    }

    fun deleteArticle(articleId: String) {
        _articlesData.value = _articlesData.value.copy(
            articles = _articlesData.value.articles.filter { it.articleId != articleId },
            filteredArticles = _articlesData.value.filteredArticles.filter { it.articleId != articleId }
        )

        this.articlesRepository.deleteArticle(articleId)
    }

    fun updateFilterKey(filterKey: String) {
        _articlesData.value = _articlesData.value.copy(filterKey = filterKey,
            filteredArticles = _articlesData.value.articles.filter { it.title.contains(filterKey, ignoreCase = true) })
    }

//    fun filterArticlesByCategory(category: String) {
//        _articlesData.value = _articlesData.value.copy(filterKey = category,
//            filteredArticles = _articlesData.value.articles.filter { it.category.name == category })
//    }

    fun findArticleById(articleId: String?): Article? {
        return _articlesData.value.articles.find { it.articleId == articleId }
    }
}