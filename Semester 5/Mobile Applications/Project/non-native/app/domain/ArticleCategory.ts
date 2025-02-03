export enum ArticleCategory {
    TECHNOLOGY = 'Technology',
    SCIENCE = 'Science',
    BUSINESS = 'Business',
    HEALTH = 'Health',
    SPORTS = 'Sports',
    EDUCATION = 'Education',
    TRAVEL = 'Travel',
    FOOD = 'Food',
}

export function getArticleCategoryFromString(category: string): ArticleCategory {
    if (category === 'Technology') {
        return ArticleCategory.TECHNOLOGY;
    }
    if (category === 'Science') {
        return ArticleCategory.SCIENCE;
    }
    if (category === 'Business') {
        return ArticleCategory.BUSINESS;
    }
    if (category === 'Health') {
        return ArticleCategory.HEALTH;
    }
    if (category === 'Sports') {
        return ArticleCategory.SPORTS;
    }
    if (category === 'Education') {
        return ArticleCategory.EDUCATION;
    }
    if (category === 'Travel') {
        return ArticleCategory.TRAVEL;
    }
    if (category === 'Food') {
        return ArticleCategory.FOOD;
    }
    return ArticleCategory.TECHNOLOGY;
    
}