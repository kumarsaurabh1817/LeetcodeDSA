class Solution {
private:
    vector<int> get_prev_smaller(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n, -1);
        stack<int> st;

        for (int i = 0; i < n; i++) {
            while (!st.empty() && nums[st.top()] >= nums[i]) {
                st.pop();
            }
            if (!st.empty()) {
                res[i] = st.top();
            }
            st.push(i);
        }
        return res;
    }

    vector<int> get_next_smaller_or_eq(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n, n);
        stack<int> st;

        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && nums[st.top()] > nums[i]) {
                st.pop();
            }
            if (!st.empty()) {
                res[i] = st.top();
            }
            st.push(i);
        }
        return res;
    }

    vector<int> get_prev_larger(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n, -1);
        stack<int> st;

        for (int i = 0; i < n; i++) {
            while (!st.empty() && nums[st.top()] <= nums[i]) {
                st.pop();
            }
            if (!st.empty()) {
                res[i] = st.top();
            }
            st.push(i);
        }
        return res;
    }

    vector<int> get_next_larger_or_eq(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n, n);
        stack<int> st;

        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && nums[st.top()] < nums[i]) {
                st.pop();
            }
            if (!st.empty()) {
                res[i] = st.top();
            }
            st.push(i);
        }
        return res;
    }

    long long compute_count(int L, int R, int i, int k, int n) {
        long long sum_total = 0;

        // Case A: s +k-1 <= R, e_max = s +k-1
        int s_start_A = max(L, i - k + 1);
        int s_end_A = min(i, R - k + 1);

        if (s_start_A <= s_end_A) {
            int a = s_start_A;
            int b = s_end_A;
            long long sum_s = (b * (b + 1LL) - (a - 1LL) * a) / 2;
            long long sum_k_i = (k - i) * (b - a + 1LL);
            sum_total += sum_s + sum_k_i;
        }

        // Case B: s +k-1 > R, e_max = R
        if (R >= i) {
            int s_start_B = max(L, R - k + 2);
            int s_end_B = i;

            if (s_start_B <= s_end_B) {
                long long count = s_end_B - s_start_B + 1LL;
                sum_total += (R - i + 1LL) * count;
            }
        }

        return sum_total;
    }
public:
    long long minMaxSubarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        if (n == 0) return 0;

        vector<int> prev_smaller = get_prev_smaller(nums);
        vector<int> next_smaller_or_eq = get_next_smaller_or_eq(nums);
        vector<int> prev_larger = get_prev_larger(nums);
        vector<int> next_larger_or_eq = get_next_larger_or_eq(nums);

        long long total = 0;

        for (int i = 0; i < n; i++) {
            // Compute count for minima
            int L_min = prev_smaller[i] + 1;
            int R_min = next_smaller_or_eq[i] - 1;
            long long count_min = compute_count(L_min, R_min, i, k, n);

            // Compute count for maxima
            int L_max = prev_larger[i] + 1;
            int R_max = next_larger_or_eq[i] - 1;
            long long count_max = compute_count(L_max, R_max, i, k, n);

            total += (long long)nums[i] * (count_min + count_max);
        }

        return total;
    }
};