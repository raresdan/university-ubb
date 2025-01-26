package com.example.articles.ui.components

import androidx.compose.foundation.layout.widthIn
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.DropdownMenuItem
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.ExposedDropdownMenuBox
import androidx.compose.material3.ExposedDropdownMenuDefaults
import androidx.compose.material3.MenuAnchorType
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
import androidx.compose.ui.unit.dp

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun OptionSelector(onItemSelected: (String) -> Unit, category: String? = null) {
    val options = arrayOf("Technology", "Science", "Business", "Health", "Sports", "Education", "Travel", "Food")
    var isExpanded by remember { mutableStateOf(false) }
    var selectedText by remember { mutableStateOf(category ?: options[0]) }

    ExposedDropdownMenuBox(
        expanded = isExpanded,
        onExpandedChange = {
            isExpanded = !isExpanded
        },
        modifier = Modifier.widthIn(max = 200.dp)
    ) {
        TextField(
            value = selectedText,
            onValueChange = {},
            readOnly = true,
            trailingIcon = { ExposedDropdownMenuDefaults.TrailingIcon(expanded = isExpanded) },
            modifier = Modifier
                .menuAnchor(type = MenuAnchorType.PrimaryNotEditable)
                .clip(RoundedCornerShape(12.dp)),
            colors = TextFieldDefaults.colors(
                focusedIndicatorColor = Color.Transparent,
                unfocusedIndicatorColor = Color.Transparent,
                disabledIndicatorColor = Color.Transparent
            )
        )

        ExposedDropdownMenu(
            expanded = isExpanded,
            onDismissRequest = { isExpanded = false }
        ) {
            options.forEach { item ->
                DropdownMenuItem(
                    text = {
                        Text(text = item)
                    },
                    onClick = {
                        selectedText = item
                        onItemSelected(item)
                        isExpanded = false
                    }
                )
            }
        }
    }
}
