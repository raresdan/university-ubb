package com.example.articles

import android.os.Bundle
import androidx.activity.compose.setContent
import androidx.appcompat.app.AppCompatActivity
import androidx.compose.material3.MaterialTheme
import androidx.compose.runtime.Composable
import androidx.hilt.navigation.compose.hiltViewModel
import androidx.navigation.NavType
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import androidx.navigation.compose.rememberNavController
import androidx.navigation.navArgument
import com.example.articles.ui.screens.AddEditScreen
import com.example.articles.ui.screens.HomeScreen
import com.example.articles.viewmodels.ArticlesViewModel
import dagger.hilt.android.AndroidEntryPoint

@AndroidEntryPoint
class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        setContent {
            App()
        }
    }
}


@Composable
fun App() {
    val navController = rememberNavController()
    val articlesViewModel: ArticlesViewModel = hiltViewModel()
    MaterialTheme {
        NavHost(navController = navController, startDestination = "main-screen") {
            composable("main-screen") {
                HomeScreen(
                    navController = navController,
                    articlesViewModel = articlesViewModel
                )
            }
            composable(
                route = "addArticle"
            ) {
                AddEditScreen(
                    articlesViewModel = articlesViewModel,
                    navController = navController
                )
            }
            composable(
                route = "editArticle/{articleId}",
                arguments = listOf(navArgument("articleId") { type = NavType.StringType })
            ) { backStackEntry ->
                AddEditScreen(
                    articleId = backStackEntry.arguments?.getString("articleId"),
                    articlesViewModel = articlesViewModel,
                    navController = navController
                )
            }
        }
    }
}