package com.example.articles.utils

import com.example.articles.domain.ArticleCategory
import com.example.articles.domain.Article
import java.util.Date

val demoArticles = listOf(
    Article(
        articleId = "1",
        title = "How to create a new project in Android Studio",
        context = "This is a step by step guide to create a new project in Android Studio. " +
                "First, open Android Studio and click on 'Start a new Android Studio project'. " +
                "Then, choose the type of project you want to create and click 'Next'. " +
                "After that, enter the name of your project and click 'Finish'. " +
                "Finally, your new project will be created and you can start developing your app.",
        author = "Rares Dan",
        date = Date(System.currentTimeMillis() - 100000000),
        category = ArticleCategory.TECHNOLOGY
    ),
    Article(
        articleId = "2",
        title = "How to make a delicious chocolate cake",
        context = "This is a recipe to make a delicious chocolate cake. " +
                "First, preheat the oven to 350 degrees Fahrenheit. " +
                "Then, mix together 1 and 3/4 cups of flour, 2 cups of sugar, 3/4 cup of cocoa powder, " +
                "1 and 1/2 teaspoons of baking powder, 1 and 1/2 teaspoons of baking soda, " +
                "1 teaspoon of salt, 2 eggs, 1 cup of milk, 1/2 cup of vegetable oil, " +
                "2 teaspoons of vanilla extract, and 1 cup of boiling water. " +
                "Pour the batter into a greased pan and bake for 30 to 35 minutes. " +
                "Finally, let the cake cool and enjoy!",
        author = "Alice Smith",
        date = Date(System.currentTimeMillis() - 200000000),
        category = ArticleCategory.FOOD
    ),
    Article(
        articleId = "3",
        title = "The benefits of meditation",
        context = "Meditation has many benefits for both the mind and body. " +
                "It can reduce stress, improve concentration, increase self-awareness, " +
                "and promote emotional health. " +
                "Meditation can also help reduce symptoms of anxiety, depression, " +
                "and insomnia. " +
                "To start meditating, find a quiet place, sit or lie down comfortably, " +
                "close your eyes, and focus on your breath. " +
                "Try to clear your mind of any thoughts and just be present in the moment. " +
                "Even just a few minutes of meditation each day can have a positive impact on your life.",
        author = "John Doe",
        date = Date(System.currentTimeMillis() - 300000000),
        category = ArticleCategory.HEALTH
    ),
    Article(
        articleId = "4",
        title = "The latest advancements in artificial intelligence",
        context = "Artificial intelligence (AI) is a rapidly evolving field " +
                "that has seen many advancements in recent years. " +
                "Some of the latest developments in AI include " +
                "natural language processing, computer vision, " +
                "and autonomous vehicles. " +
                "AI is being used in a wide range of industries, " +
                "from healthcare and finance to transportation and entertainment. " +
                "As AI continues to develop, it has the potential to " +
                "revolutionize the way we live and work.",
        author = "Jane Smith",
        date = Date(System.currentTimeMillis() - 400000000),
        category = ArticleCategory.TECHNOLOGY
    ),
    Article(
        articleId = "5",
        title = "The importance of exercise",
        context = "Exercise is essential for maintaining good health " +
                "and preventing chronic diseases. " +
                "Regular physical activity can help you control your weight, " +
                "reduce your risk of heart disease, " +
                "and strengthen your muscles and bones. " +
                "Exercise can also improve your mental health, " +
                "boost your mood, and reduce feelings of anxiety and depression. " +
                "To stay healthy, aim for at least 150 minutes of moderate-intensity exercise " +
                "or 75 minutes of vigorous-intensity exercise each week.",
        author = "Alex Johnson",
        date = Date(System.currentTimeMillis()),
        category = ArticleCategory.HEALTH
    ),
    Article(
        articleId = "6",
        title = "The future of space exploration",
        context = "Space exploration is an exciting and rapidly evolving field " +
                "that has the potential to revolutionize our understanding of the universe. " +
                "In the coming years, we can expect to see " +
                "more missions to Mars, the Moon, and beyond. " +
                "Advancements in technology, such as reusable rockets " +
                "and artificial intelligence, are making space travel more accessible " +
                "and affordable. " +
                "As we continue to explore the cosmos, " +
                "we will gain new insights into the origins of the universe " +
                "and the possibility of life on other planets.",
        author = "Sarah Brown",
        date = Date(System.currentTimeMillis() - 200000000),
        category = ArticleCategory.SCIENCE
    ),
    Article(
        articleId = "7",
        title = "The benefits of reading",
        context = "Reading has many benefits for the mind and body. " +
                "It can improve your vocabulary, enhance your memory, " +
                "and reduce stress. " +
                "Reading can also increase your empathy, " +
                "expand your knowledge, and boost your creativity. " +
                "To get the most out of reading, " +
                "try to read a variety of genres and authors. " +
                "Whether you prefer fiction or non-fiction, " +
                "reading regularly can have a positive impact on your life.",
        author = "David Wilson",
        date = Date(System.currentTimeMillis()),
        category = ArticleCategory.EDUCATION
    ),
    Article(
        articleId = "8",
        title = "The benefits of a plant-based diet",
        context = "A plant-based diet has many health benefits " +
                "and can help prevent chronic diseases. " +
                "Plant-based foods are rich in vitamins, minerals, " +
                "and antioxidants that can boost your immune system " +
                "and reduce inflammation. " +
                "Eating a plant-based diet can also help you " +
                "maintain a healthy weight, improve your digestion, " +
                "and reduce your risk of heart disease and cancer. " +
                "To adopt a plant-based diet, focus on eating " +
                "a variety of fruits, vegetables, whole grains, " +
                "nuts, seeds, and legumes.",
        author = "Emily Jones",
        date = Date(System.currentTimeMillis()),
        category = ArticleCategory.HEALTH
    ),
    Article(
        articleId = "9",
        title = "The benefits of learning a new language",
        context = "Learning a new language has many cognitive " +
                "and social benefits. " +
                "It can improve your memory, enhance your " +
                "problem-solving skills, and boost your creativity. " +
                "Learning a new language can also increase " +
                "your cultural awareness, help you connect with others, " +
                "and open up new opportunities for travel and work. " +
                "To start learning a new language, " +
                "try taking a class, using language learning apps, " +
                "or practicing with a native speaker.",
        author = "Michael Brown",
        date = Date(System.currentTimeMillis()),
        category = ArticleCategory.EDUCATION
    ),
    Article(
        articleId = "10",
        title = "The benefits of volunteering",
        context = "Volunteering has many benefits for both " +
                "the volunteer and the community. " +
                "It can improve your mental health, " +
                "increase your sense of purpose, and boost your self-esteem. " +
                "Volunteering can also help you develop new skills, " +
                "expand your social network, and make a positive impact " +
                "on the lives of others. " +
                "To get involved in volunteering, " +
                "look for opportunities in your local community " +
                "or with organizations that align with your interests.",
        author = "Laura Smith",
        date = Date(System.currentTimeMillis() - 500000000),
        category = ArticleCategory.EDUCATION
    ),
    // Add more articles here from tech. do not repeat
    Article(
        articleId = "11",
        title = "The benefits of learning a new programming language",
        context = "Learning a new programming language can " +
                "expand your skill set, increase your job opportunities, " +
                "and boost your earning potential. " +
                "Programming languages are used in a wide range of industries, " +
                "from software development and web design to data analysis and artificial intelligence. " +
                "To start learning a new programming language, " +
                "try taking an online course, reading a book, " +
                "or working on a personal project. " +
                "Whether you're a beginner or an experienced programmer, " +
                "learning a new language can help you stay competitive in the tech industry.",
        author = "Daniel Johnson",
        date = Date(System.currentTimeMillis()),
        category = ArticleCategory.TECHNOLOGY
    ),
    Article(
        articleId = "12",
        title = "Top 10 best programming languages to learn in 2025",
        context = "Programming languages are constantly evolving " +
                "and new languages are emerging every year. " +
                "In 2025, some of the top programming languages to learn include " +
                "Python, JavaScript, Java, C++, and Swift. " +
                "These languages are in high demand in the tech industry " +
                "and can help you land a job at top companies. " +
                "Whether you're interested in web development, " +
                "mobile app development, or data science, " +
                "learning one of these languages can give you a competitive edge in your career.",
        author = "Sophia Wilson",
        date = Date(System.currentTimeMillis() - 600000000),
        category = ArticleCategory.HEALTH
    ),
)