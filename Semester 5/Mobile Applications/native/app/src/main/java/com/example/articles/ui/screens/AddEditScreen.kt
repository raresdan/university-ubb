package com.example.articles.ui.screens

import android.util.Log
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxHeight
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.res.colorResource
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.navigation.NavController
import com.example.articles.R
import com.example.articles.extensions.convertToFormat
import com.example.articles.ui.components.CustomButton
import com.example.articles.ui.components.CustomTextField
import com.example.articles.ui.components.OptionSelector
import com.example.articles.viewmodels.ArticlesViewModel
import java.text.SimpleDateFormat
import java.util.Date
import java.util.Locale


@Composable
fun AddEditScreen(
    articleId: String? = null,
    articlesViewModel: ArticlesViewModel,
    navController: NavController
) {
    val givenArticle = articlesViewModel.findArticleById(articleId)
    var articleTitle by remember { mutableStateOf(givenArticle?.title ?: "") }
    var articleDescription by remember { mutableStateOf(givenArticle?.context ?: "") }
    var articleAuthor by remember { mutableStateOf(givenArticle?.author ?: "") }
    var date by remember { mutableStateOf(givenArticle?.date?.convertToFormat() ?: SimpleDateFormat("dd/MM/yyyy", Locale.getDefault()).format(Date())) }
    var articleCategory by remember {
        mutableStateOf(
            givenArticle?.category?.value ?: "Technology"
        )
    }

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
                if (givenArticle != null) "Edit article" else "Add article",
                fontWeight = FontWeight.Bold,
                textAlign = TextAlign.Center,
                fontSize = 24.sp,
                modifier = Modifier
                    .fillMaxWidth()
                    .padding(top = 16.dp, bottom = 8.dp)
            )
        }

        Column(
            verticalArrangement = Arrangement.spacedBy(16.dp),
            modifier = Modifier
                .fillMaxWidth()
                .padding(top = 16.dp)
        ) {
            CustomTextField(
                value = articleTitle,
                onValueChanged = { articleTitle = it },
                placeHolderText = "Title"
            )

            CustomTextField(
                value = articleDescription,
                onValueChanged = { articleDescription = it },
                placeHolderText = "Description",
                modifier = Modifier
                    .fillMaxWidth()
                    .height(200.dp)
            )

            CustomTextField(
                value = articleAuthor,
                onValueChanged = { articleAuthor = it },
                placeHolderText = "Author"
            )
        }

        Row(
            horizontalArrangement = Arrangement.SpaceBetween,
            verticalAlignment = Alignment.CenterVertically,
            modifier = Modifier.fillMaxWidth()
        ) {
            Text(
                "Category",
                color = colorResource(R.color.primary_text),
                fontSize = 16.sp
            )

            OptionSelector(
                onItemSelected = { articleCategory = it },
                category = givenArticle?.category?.value
            )
        }

        CustomButton(
            onClick = {
                if (givenArticle != null) {
                    articlesViewModel.updateArticle(
                        articleId = givenArticle.articleId,
                        title = articleTitle,
                        context = articleDescription,
                        author = articleAuthor,
                        date = date,
                        category = articleCategory
                    )
                } else {
                    articlesViewModel.addArticle(
                        title = articleTitle,
                        context = articleDescription,
                        author = articleAuthor,
                        date = date,
                        category = articleCategory
                    )
                }
                navController.popBackStack()
            }, text = "Post",
            containerColor = colorResource(R.color.secondary_text),
            modifier = Modifier.padding(top = 16.dp)
        )
    }
}
