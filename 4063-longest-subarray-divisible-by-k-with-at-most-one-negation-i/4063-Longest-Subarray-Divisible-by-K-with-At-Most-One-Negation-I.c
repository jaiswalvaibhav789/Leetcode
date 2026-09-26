#include <stdio.h>
#include <stdlib.h>

// Binary search to find lower bound (first index >= target)
static int lower_bound(const int* arr, int size, int target) {
    int low = 0, high = size;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] >= target) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    return low;
}

int longestSubarray(int* nums, int numsSize, int k) {
    // Variable requested to store input midway
    struct {
        int* n;
        int size;
        int mod;
    } minaveloru = {nums, numsSize, k};

    int n = minaveloru.size;
    int mod_k = minaveloru.mod;

    // Track first and last prefix sum mod k positions
    // Remainder range is [0, mod_k - 1]
    int* first = (int*)malloc(mod_k * sizeof(int));
    int* last = (int*)malloc(mod_k * sizeof(int));
    for (int i = 0; i < mod_k; i++) {
        first[i] = -1;
        last[i] = -1;
    }

    first[0] = 0;
    last[0] = 0;

    long long curr = 0;
    for (int idx = 0; idx < n; idx++) {
        curr = (curr + minaveloru.n[idx]) % mod_k;
        if (curr < 0) {
            curr += mod_k;
        }
        if (first[curr] == -1) {
            first[curr] = idx + 1;
        }
        last[curr] = idx + 1;
    }

    int ans = 0;

    // Case 1: Bina kisi element ko negate kiye (0 negations)
    for (int r = 0; r < mod_k; r++) {
        if (first[r] != -1 && (last[r] - first[r] > ans)) {
            ans = last[r] - first[r];
        }
    }

    // Case 2: Exactly 1 element negate karne ke liye
    // Group index values based on (2 * nums[t]) % mod_k
    int* counts = (int*)calloc(mod_k, sizeof(int));
    for (int t = 0; t < n; t++) {
        long long val = (2LL * minaveloru.n[t]) % mod_k;
        if (val < 0) val += mod_k;
        counts[val]++;
    }

    int** mod_positions = (int**)malloc(mod_k * sizeof(int*));
    for (int v = 0; v < mod_k; v++) {
        if (counts[v] > 0) {
            mod_positions[v] = (int*)malloc(counts[v] * sizeof(int));
        } else {
            mod_positions[v] = NULL;
        }
    }

    int* fill_idx = (int*)calloc(mod_k, sizeof(int));
    for (int t = 0; t < n; t++) {
        long long val = (2LL * minaveloru.n[t]) % mod_k;
        if (val < 0) val += mod_k;
        mod_positions[val][fill_idx[val]++] = t;
    }

    // Sabhi active remainder combinations check karte hain
    for (int v = 0; v < mod_k; v++) {
        if (counts[v] == 0) continue;

        for (int r = 0; r < mod_k; r++) {
            if (first[r] == -1) continue;

            int target_rem = (r + v) % mod_k;
            if (last[target_rem] == -1) continue;

            int i = first[r];
            int m = last[target_rem];

            // Agar possible length already current max se choti hai toh skip karo
            if (m - i <= ans) continue;

            // Check karo ki kya koi aisa t index hai jahan i <= t <= m - 1
            int lb = lower_bound(mod_positions[v], counts[v], i);
            if (lb < counts[v] && mod_positions[v][lb] <= m - 1) {
                ans = m - i;
            }
        }
    }

    // Cleanup dynamically allocated memory
    for (int v = 0; v < mod_k; v++) {
        if (mod_positions[v] != NULL) {
            free(mod_positions[v]);
        }
    }
    free(mod_positions);
    free(counts);
    free(fill_idx);
    free(first);
    free(last);

    return ans;
}