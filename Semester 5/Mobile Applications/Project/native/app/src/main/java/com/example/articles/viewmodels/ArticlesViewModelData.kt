package com.example.articles.viewmodels

import com.example.articles.domain.Article

data class ArticlesViewModelData (
    val articles: List<Article> = emptyList(),
    val filteredArticles: List<Article> = emptyList(),
    val filterKey: String = ""
)