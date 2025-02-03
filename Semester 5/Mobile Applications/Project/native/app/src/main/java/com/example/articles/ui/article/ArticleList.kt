package com.example.articles.ui.article

import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.itemsIndexed
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.unit.sp
import com.example.articles.extensions.convertToFormat
import com.example.articles.viewmodels.ArticlesViewModel


@Composable
fun ArticleList(
    modifier: Modifier = Modifier,
    onEditArticle: (String) -> Unit,
    articlesViewModel: ArticlesViewModel
) {
    val articlesViewModelData by articlesViewModel.articlesData.collectAsState()

    if (articlesViewModelData.filteredArticles.isEmpty())
        Column(
            verticalArrangement = Arrangement.Center,
            modifier = modifier
        ) {
            Text(
                "Oops! No article with this title!",
                fontSize = 24.sp
            )
        }
    else
        LazyColumn(modifier = modifier) {
            itemsIndexed(articlesViewModelData.filteredArticles) { _, article ->
                ArticleCard(article = article,
                    onEditArticle = onEditArticle,
                    onStatusChanged = {
                        articlesViewModel.updateArticle(
                            articleId = article.articleId,
                            title = article.title,
                            context = article.context,
                            author = article.author,
                            date = article.date?.convertToFormat() ?: "",
                            category = article.category.value
                        )
                    },
                    onDeleteArticle = { articlesViewModel.deleteArticle(article.articleId) })
            }
        }
}