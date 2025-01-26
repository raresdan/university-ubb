package com.example.articles.ui.components



import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.shape.CircleShape
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.res.colorResource
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.example.articles.R

@Composable
fun CustomRoundButton(onClick: () -> Unit,
                 text: String,
                 enabled: Boolean = true,
                 containerColor: Color = Color.Unspecified,
                 modifier: Modifier = Modifier){
    Box(
        contentAlignment = Alignment.Center,
        modifier = modifier
            .size(48.dp)
            .background(containerColor, CircleShape)
            .clickable(onClick = onClick)
    ) {
        Text(
            text = text,
            color = colorResource(R.color.white),
            fontSize = 24.sp,
            fontWeight = FontWeight.Bold
        )
    }
}