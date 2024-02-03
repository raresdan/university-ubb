package source.models.utils;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class MyDictionary<TKey, TValue> implements MyIDictionary<TKey, TValue> {
    private final Map<TKey, TValue> dictionary;

    public MyDictionary() {
        this.dictionary = new HashMap<TKey, TValue>();
    }

    @Override
    public TValue get(TKey keyToSearchFor) {
        return this.dictionary.get(keyToSearchFor);
    }

    @Override
    public void put(TKey keyToAdd, TValue valueToAdd) {
        this.dictionary.put(keyToAdd, valueToAdd);
    }

    @Override
    public void update(TKey keyToUpdate, TValue newValue) {
        this.dictionary.put(keyToUpdate, newValue);
    }

    @Override
    public boolean isDefined(TKey keyToSearchFor) {
        return dictionary.containsKey(keyToSearchFor);
    }

    @Override
    public Set<TKey> getKeySet() {
        return this.dictionary.keySet();
    }

    @Override
    public Map<TKey, TValue> getContent() {
        return this.dictionary;
    }

    @Override
    public void remove(TKey keyToRemove) {
        this.dictionary.remove(keyToRemove);
    }

    @Override
    public String toString() {
        return "MyDictionary{" + "dictionary=" + this.dictionary + '}';
    }

    @Override
    public MyIDictionary<TKey, TValue> copy() {
        MyIDictionary<TKey, TValue> dictionaryCopy = new MyDictionary<>();

        for (TKey key : this.getKeySet())
            dictionaryCopy.put(key, this.get(key));

        return dictionaryCopy;
    }
}
