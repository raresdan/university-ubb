package com.example.articles.domain;

import java.util.Date


data class Article(
    val articleId: String,
    val title: String,
    val context: String,
    val author: String,
    val date: Date?,
    val category: ArticleCategory
    )