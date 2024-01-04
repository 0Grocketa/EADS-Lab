#include"sequence.hpp"
#include <iostream>

template <typename Key, typename Info>
void split_pos(Sequence<Key, Info>& seq, int start_pos, int len1, int len2, int count, Sequence<Key, Info>& seq1, Sequence<Key, Info>& seq2) {
    if (start_pos < 0 || len1 < 0 || len2 < 0 || count < 0) {
        return;
    }

    for (int totalCount = 0; totalCount < count; ++totalCount) {
        int currentPos = start_pos;
        for (int i = 0; i < len1 && currentPos < seq.size(); ++i) {
            Key key;
            Info info;
            if (seq.getInfo(info, key, currentPos + 1)) {
                seq1.push_back(key, info);
                seq.remove_at(currentPos);
            } else {
                break;
            }
        }
        for (int i = 0; i < len2 && currentPos < seq.size(); ++i) {
            Key key;
            Info info;
            if (seq.getInfo(info, key, currentPos + 1)) {
                seq2.push_back(key, info);
                seq.remove_at(currentPos);
            } else {
                break;
            }
        }
    }
}


template <typename Key, typename Info>
void split_key(Sequence<Key, Info>& seq, const Key& start_key, int start_occ, int len1, int len2, int count, Sequence<Key, Info>& seq1, Sequence<Key, Info>& seq2) {
    if (start_occ < 1 || len1 < 0 || len2 < 0 || count < 0) {
        return;
    }

    int currentOccurrence = 0;
    int currentIndex = 0;

    while (currentIndex < seq.size() && currentOccurrence < start_occ) {
        Key key;
        Info info;
        if (seq.getInfo(info, key, currentIndex + 1)) {
            if (key == start_key) {
                currentOccurrence++;
                if (currentOccurrence == start_occ) {
                    break; // Found the start position
                }
            }
        }
        currentIndex++;
    }

    if (currentOccurrence < start_occ) {
        return;
    }


    for (int totalCount = 0; totalCount < count && currentIndex < seq.size(); ++totalCount) {
        for (int i = 0; i < len1 && currentIndex < seq.size(); ++i) {
            Key key;
            Info info;
            if (seq.getInfo(info, key, currentIndex + 1)) {
                seq1.push_back(key, info);
                seq.remove_at(currentIndex);
            }
        }
        for (int i = 0; i < len2 && currentIndex < seq.size(); ++i) {
            Key key;
            Info info;
            if (seq.getInfo(info, key, currentIndex + 1)) {
                seq2.push_back(key, info);
                seq.remove_at(currentIndex);
            }
        }
    }
}

template <typename Key, typename Info>
Sequence<Key, Info> merge(const Sequence<Key, Info>& seq1, const Sequence<Key, Info>& seq2) {
    Sequence<Key, Info> mergedSeq;
    if (seq1.is_empty()) {
        // If seq1 is empty, return a copy of seq2 (or an empty sequence if seq2 is also empty)
        return mergedSeq = seq2;
    }

    if (seq2.is_empty()) {
        // If seq2 is empty, return a copy of seq1
        return mergedSeq = seq1;
    }

    int middlePos = seq1.size() / 2; // Calculate the middle position
    Key key;
    Info info;

    // Insert elements of seq1 up to middle position into mergedSeq
    for (int i = 0; i < middlePos; ++i) {
        if (seq1.getInfo(info, key, i + 1)) {
            mergedSeq.push_back(key, info);
        }
    }

    // Insert the first element of seq2 into mergedSeq
    if (seq2.getInfo(info, key, 1)) {
        mergedSeq.push_back(key, info);
    }

    // Insert the remaining elements of seq1 into mergedSeq
    for (int i = middlePos; i < seq1.size(); ++i) {
        if (seq1.getInfo(info, key, i + 1)) {
            mergedSeq.push_back(key, info);
        }
    }

    return mergedSeq;
}





