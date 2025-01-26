package com.example.articles.ui.screens

import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxHeight
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.shape.CircleShape
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.res.colorResource
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.navigation.NavController
import com.example.articles.R
import com.example.articles.ui.article.ArticleList
import com.example.articles.ui.components.CustomButton
import com.example.articles.ui.components.CustomRoundButton
import com.example.articles.viewmodels.ArticlesViewModel
import com.example.articles.ui.components.SearchBar

@Composable
fun HomeScreen(navController: NavController, articlesViewModel: ArticlesViewModel) {
    val articlesViewModelData by articlesViewModel.articlesData.collectAsState()

    Column(
        verticalArrangement = Arrangement.SpaceBetween,
        horizontalAlignment = Alignment.CenterHorizontally,
        modifier = Modifier
            .fillMaxWidth()
            .fillMaxHeight()
            .background(color = Color(0xFFF7FAFA))
            .padding(all = 16.dp)
    ) {
        // Header
        Column {
            Text(
                "Articles",
                fontWeight = FontWeight.Bold,
                textAlign = TextAlign.Center,
                fontSize = 24.sp,
                modifier = Modifier
                    .fillMaxWidth()
                    .padding(top = 16.dp, bottom = 8.dp)

            )
            Row(
                horizontalArrangement = Arrangement.SpaceBetween,
                verticalAlignment = Alignment.CenterVertically,
                modifier = Modifier.fillMaxWidth()
            ) {
                SearchBar(
                    articlesViewModel::updateFilterKey,
                    searchQuery = articlesViewModelData.filterKey

                )

                CustomRoundButton(
                    text = " + ",
                    onClick = { navController.navigate("addArticle") },
                    containerColor = colorResource(id = R.color.secondary_text),
                    modifier = Modifier
                        .padding(start = 8.dp)
                        .size(48.dp)
                        .clip(CircleShape)
                )
            }
        }
        ArticleList(
            modifier = Modifier.weight(1f),
            onEditArticle = { navController.navigate("editArticle/$it") },
            articlesViewModel = articlesViewModel
        )

    }
}