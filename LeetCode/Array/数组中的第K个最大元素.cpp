/* 暴力法：
 * 调用库函数对数组进行原地快排，
 * 排好后的倒数第k的元素就是
 * 数组中的第K个最大元素
 * 时间复杂度：O(nlogn) => 快排的平均时间复杂度，
 * 空间复杂度：O(logn) => 数组的递归调用栈深度 */
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        std::sort(nums.begin(), nums.end(), [&](int x, int y) { return x > y; });
        return nums[k - 1];
    }
};

/* 多重集合 */
/* 时间复杂度: O(n) */
/* 空间复杂度: O(n) */
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        std::multiset<int, std::greater<int>> s(nums.begin(), nums.end());
        for (auto& n : s) {
            if (k == 1) return n;
            --k;
        }
        return INT_MAX;
    }
};

/* 优先级队列 ——— 小顶堆
 * 维护一个容量为k的小顶堆，
 * 堆顶是第K个最大的数，
 * 本题可直接使用STL中的
 * priority_queue来实现相关算法。
 * 时间复杂度: O(nlogn)
 * 空间复杂度: O(logn) => 堆排序递归调用栈空间的深度 */
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        std::priority_queue<int, std::vector<int>, std::less<int>> pq(nums.begin(), nums.end());
        while (--k) pq.pop();
        return pq.top();
    }
};

/* 减治法：
 * 利用每一次快排可以确定一个元素
 * 在数组中的绝对位置的特性，并且每次
 * 从最内层的while跳出后能缩小到为原来一半的搜索范围。
 * 通过这样“减而治之”的思想实现数组中的第K大元素的查找
 * 时间复杂度: O(n)
 * 空间复杂度: O(1) */
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int low = 0, high = nums.size() - 1, len = nums.size();
        while (true) {
            int l = low, h = high;
            while (l < h) {
                while (l < h && nums[h] >= nums[low]) --h;
                while (l < h && nums[l] <= nums[low]) ++l;
                std::swap(nums[l], nums[h]);
            }
            std::swap(nums[l], nums[low]);
            if (l == len - k)
                return nums[l];
            else if (l < len - k)
                low = l + 1;
            else if (l > len - k)
                high = l - 1;
        }
    }
};
