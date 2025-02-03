package com.example.articles.ui.components

import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.Icon
import androidx.compose.material3.Text
import androidx.compose.material3.TextField
import androidx.compose.material3.TextFieldDefaults
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.res.colorResource
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.example.articles.R

@Composable
fun SearchBar(onValueChanged: (String) -> Unit, searchQuery: String = "") {
    var text by remember { mutableStateOf(searchQuery) }

    Box(
        modifier = Modifier
            .padding(top = 12.dp, bottom = 12.dp)
    ) {
        TextField(
            value = text,
            onValueChange = {
                text = it
                onValueChanged(it)
            },
                placeholder = {
                    Text(
                        "Search...",
                        style = TextStyle(
                            fontSize = 16.sp,
                            color = colorResource(R.color.secondary_text)
                        )
                    )
                },

            leadingIcon = {
                Icon(
                    painter = painterResource(id = R.drawable.search_icon),
                    contentDescription = "Search icon",
                    modifier = Modifier.size(24.dp),
                    tint = colorResource(R.color.secondary_text)
                )
            },

            textStyle = TextStyle(fontSize = 16.sp, color = colorResource(R.color.primary_text)),

            colors = TextFieldDefaults.colors(
                focusedIndicatorColor = Color.Transparent,
                unfocusedIndicatorColor = Color.Transparent,
                disabledIndicatorColor = Color.Transparent
            ),

            modifier = Modifier
                .height(48.dp)
                .clip(RoundedCornerShape(12.dp))
                .background(color = Color(0xFFE8EDF2)),
        )
    }
}