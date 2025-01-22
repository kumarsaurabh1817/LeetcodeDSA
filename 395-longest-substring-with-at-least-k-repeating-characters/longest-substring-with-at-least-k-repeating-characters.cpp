class Solution {
public:
    int longestSubstring(string s, int k) {
        int maxUniqueCharCount = getUniqueCharCount(s);
        vector<int> freqMap(26, 0);
        int result = 0;

        for (int currentUniqueChar = 1; currentUniqueChar <= maxUniqueCharCount; currentUniqueChar++) {
            fill(freqMap.begin(), freqMap.end(), 0);
            int uniqueCount = 0, countAtLeastK = 0, windowStart = 0, windowEnd = 0;

            while (windowEnd < s.length()) {
                if (uniqueCount <= currentUniqueChar) {
                    int idx = s[windowEnd] - 'a';
                    if (freqMap[idx] == 0) {
                        uniqueCount++;
                    }
                    freqMap[idx]++;

                    if (freqMap[idx] == k) {
                        countAtLeastK++;
                    }
                    windowEnd++;
                } else {
                    // Shrink the window
                    int idx = s[windowStart] - 'a';
                    if (freqMap[idx] == k) {
                        countAtLeastK--;
                    }
                    freqMap[idx]--;
                    if (freqMap[idx] == 0) {
                        uniqueCount--;
                    }
                    windowStart++;
                }

                if (uniqueCount == currentUniqueChar && uniqueCount == countAtLeastK) {
                    result = max(windowEnd - windowStart, result);
                }
            }
        }

        return result;
    }

private:
    int getUniqueCharCount(const string& s) {
        unordered_set<char> chars(s.begin(), s.end());
        return chars.size();
    }
};