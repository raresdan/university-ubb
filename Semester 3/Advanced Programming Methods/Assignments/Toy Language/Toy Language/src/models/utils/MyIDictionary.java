package models.utils;

import java.util.Map;
import java.util.Set;

public interface MyIDictionary<TKey, TValue> {
    TValue get(TKey keyToSearchFor);

    void put(TKey keyToAdd, TValue valueToAdd);

    void update(TKey keyToUpdate, TValue newValue);

    boolean isDefined(TKey keyToSearchFor);

    Set<TKey> getKeySet();

    Map<TKey, TValue> getContent();

    void remove(TKey keyToRemove);

    MyIDictionary<TKey, TValue> copy();
}
