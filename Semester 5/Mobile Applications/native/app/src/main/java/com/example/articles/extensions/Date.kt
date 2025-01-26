package com.example.articles.extensions

import java.text.SimpleDateFormat
import java.util.Date
import java.util.Locale

fun Date.convertToFormat(format: String = "dd/MM/yyyy"): String {
    val dateFormat = SimpleDateFormat(format, Locale.getDefault())
    return dateFormat.format(this)
}