package com.example.articles.modules


import dagger.Module
import dagger.Provides
import dagger.hilt.InstallIn
import dagger.hilt.components.SingletonComponent
import javax.inject.Singleton
import com.example.articles.repository.InMemoryRepository

@Module
@InstallIn(SingletonComponent::class)
class AppModule {
    @Provides
    @Singleton
    fun provideArticleRepository(): InMemoryRepository {
        return InMemoryRepository()
    }
}