#include <iostream>
#include <vector>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>  // Make sure to include this for std::find

using namespace std;
void simulate_fifo(const std::vector<int>& pages, int frame_count) {
    std::list<int> queue;
    std::unordered_set<int> in_memory;
    int page_faults = 0;

    for (size_t i = 0; i < pages.size(); i++) {
        int current_page = pages[i];
        if (in_memory.find(current_page) == in_memory.end()) { // Page fault
            if (in_memory.size() == frame_count) { // No space left
                int oldest_page = queue.front();
                queue.pop_front();
                in_memory.erase(oldest_page);
            }
            in_memory.insert(current_page);
            queue.push_back(current_page);
            page_faults++;
            std::cout << "Step " << i + 1 << ": Page fault (" << current_page << ") - Frames: [";
        } else {
            std::cout << "Step " << i + 1 << ": No page fault (" << current_page << ") - Frames: [";
        }
        for (auto it = queue.begin(); it != queue.end(); ++it) {
            if (it != queue.begin()) std::cout << ", ";
            std::cout << *it;
        }
        std::cout << "], Faults: " << page_faults << std::endl;
    }
    std::cout << "Total Page Faults: " << page_faults << std::endl;
}


void simulate_lru(const std::vector<int>& pages, int frame_count) {
    std::list<int> lru_queue;
    std::unordered_map<int, std::list<int>::iterator> page_map;
    int page_faults = 0;

    for (size_t i = 0; i < pages.size(); i++) {
        int current_page = pages[i];
        if (page_map.find(current_page) == page_map.end()) { // Page not in memory
            if (lru_queue.size() == frame_count) { // No space left
                int least_recent = lru_queue.back();
                lru_queue.pop_back();
                page_map.erase(least_recent);
            }
            lru_queue.push_front(current_page);
            page_map[current_page] = lru_queue.begin();
            page_faults++;
            std::cout << "Step " << i + 1 << ": Page fault (" << current_page << ") - Frames: [";
        } else { // Page is in memory, refresh its position
            lru_queue.erase(page_map[current_page]);
            lru_queue.push_front(current_page);
            page_map[current_page] = lru_queue.begin();
            std::cout << "Step " << i + 1 << ": No page fault (" << current_page << ") - Frames: [";
        }
        for (auto it = lru_queue.begin(); it != lru_queue.end(); ++it) {
            if (it != lru_queue.begin()) std::cout << ", ";
            std::cout << *it;
        }
        std::cout << "], Faults: " << page_faults << std::endl;
    }
    std::cout << "Total Page Faults: " << page_faults << std::endl;
}
void simulate_optimal(const std::vector<int>& pages, int frame_count) {
    std::unordered_set<int> in_memory;
    std::vector<int> memory_frames(frame_count, -1); // Frame array
    int page_faults = 0;

    for (size_t i = 0; i < pages.size(); i++) {
        int current_page = pages[i];
        if (in_memory.find(current_page) == in_memory.end()) { // Page fault
            int replace_idx = -1, farthest = i;
            for (int j = 0; j < frame_count; j++) {
                if (memory_frames[j] == -1) { // Empty frame found
                    replace_idx = j;
                    break;
                }
                int next_use = std::find(pages.begin() + i + 1, pages.end(), memory_frames[j]) - pages.begin();
                if (next_use > farthest) {
                    farthest = next_use;
                    replace_idx = j;
                }
            }
            if (replace_idx == -1) replace_idx = 0; // Default replacement
            in_memory.erase(memory_frames[replace_idx]);
            memory_frames[replace_idx] = current_page;
            in_memory.insert(current_page);
            page_faults++;
            std::cout << "Step " << i + 1 << ": Page fault (" << current_page << ") - Frames: [";
        } else {
            std::cout << "Step " << i + 1 << ": No page fault (" << current_page << ") - Frames: [";
        }
        for (int frame : memory_frames) {
            if (frame != -1) std::cout << frame << ", ";
        }
        std::cout << "\b\b], Faults: " << page_faults << std::endl;
    }
    std::cout << "Total Page Faults: " << page_faults << std::endl;
}

int main() {
    std::vector<int> pages = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int frame_count = 4;

    std::cout << "For FIFO Algorithm:" << std::endl;
    simulate_fifo(pages, frame_count);
    std::cout << "\nFor LRU Algorithm:" << std::endl;
    simulate_lru(pages, frame_count);
    std::cout << "\nFor Optimal Algorithm:" << std::endl;
    simulate_optimal(pages, frame_count);

    return 0;
}
