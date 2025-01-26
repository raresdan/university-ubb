package com.example.articles.ui.article

import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.wrapContentWidth
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.AlertDialog
import androidx.compose.material3.Icon
import androidx.compose.material3.Text
import androidx.compose.material3.TextButton
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.res.colorResource
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.example.articles.R
import com.example.articles.domain.Article
import com.example.articles.extensions.convertToFormat

const val maxLength = 100

@Composable
fun ArticleCard(
    article: Article,
    onStatusChanged: (String) -> Unit,
    onEditArticle: (String) -> Unit,
    onDeleteArticle: (String) -> Unit
) {
    var showDialog by remember { mutableStateOf(false) }

    Column(
        verticalArrangement = Arrangement.SpaceBetween,
        modifier = Modifier
            .fillMaxWidth()
            .padding(8.dp)
    ) {
        Text(
            text = article.title,
            fontSize = 16.sp,
            fontWeight = FontWeight.Bold,
            modifier = Modifier.padding(bottom = 4.dp)
        )
        Row(
            verticalAlignment = Alignment.CenterVertically
        ) {
            Text(
                text = article.author,
                color = colorResource(R.color.secondary_text),
                fontSize = 14.sp,
                modifier = Modifier.padding(bottom = 4.dp)
            )
            Spacer(modifier = Modifier.weight(1f))
            Text(
                text = article.date?.convertToFormat().toString(),
                color = colorResource(R.color.secondary_text),
                fontSize = 14.sp,
                modifier = Modifier.padding(bottom = 4.dp)
            )
        }
        Box(
            modifier = Modifier
                .padding(bottom = 8.dp)
                .clip(RoundedCornerShape(50))
                .background(color = colorResource(R.color.secondary_text))
                .padding(horizontal = 12.dp, vertical = 4.dp)
        ) {
            Text(
                text = article.category.toString(),
                color = colorResource(R.color.white),
                fontSize = 12.sp
            )
        }
        Text(
            text = if (article.context.length > maxLength) {
                article.context.substring(0, maxLength) + "..."
            } else {
                article.context
            },
            color = colorResource(R.color.secondary_text),
            fontSize = 14.sp,
            modifier = Modifier.padding(bottom = 8.dp)
        )


        Row(
            verticalAlignment = Alignment.CenterVertically,
            horizontalArrangement = Arrangement.End
        ) {
            Icon(
                painter = painterResource(id = R.drawable.edit),
                contentDescription = "Edit",
                modifier = Modifier
                    .padding(start = 8.dp)
                    .clickable {
                        onEditArticle(article.articleId)
                    }
            )

            Icon(
                painter = painterResource(id = R.drawable.trash),
                contentDescription = "Delete",
                modifier = Modifier
                    .padding(start = 8.dp)
                    .clickable {
                        showDialog = true
                    }
            )
        }
    }

    if (showDialog) {
        AlertDialog(
            onDismissRequest = { showDialog = false },
            title = { Text("Delete confirmation") },
            text = { Text("Are you sure you want to remove this article?") },
            confirmButton = {
                TextButton(
                    onClick = {
                        onDeleteArticle(article.articleId)
                        showDialog = false
                    }
                ) {
                    Text("Delete")
                }
            },
            dismissButton = {
                TextButton(
                    onClick = { showDialog = false }
                ) {
                    Text("Cancel")
                }
            }
        )
    }
}