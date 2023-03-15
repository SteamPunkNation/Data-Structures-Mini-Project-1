#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using std::cin;
using std::cout;
using std::priority_queue;
using std::queue;
using std::vector;

// worker class to be used in the priortiy queue
class Worker {
public:
  long long next_free_time; // next free time
  int i;                    // id of worker

  bool operator>(const Worker &w2) const {
    // if multiple threads are open then the one with the lower ID will take it
    if (this->next_free_time == w2.next_free_time) {
      return this->i > w2.i;
    }
    return (this->next_free_time > w2.next_free_time);
  }
};

class JobQueue {
private:
  // number of threads, or 'n'
  int num_workers_;
  // queue of jobs
  queue<int> pq;

  // output of workers
  vector<int> assigned_workers_;
  // output of start times
  vector<long long> start_times_;

  // takes the input and turns it into data
  void ReadData() {
    int m;
    // input the number of workers "n" and number of jobs "m"
    cin >> num_workers_ >> m;
    // populate jobs queue of "m" size
    for (int i = 0; i < m; ++i) {
      int j;
      cin >> j;
      pq.push(j);
    }
    // resize output list to fit amount of jobs
    assigned_workers_.resize(m);
    start_times_.resize(m);
  }

  void AssignJobs() {

    // current job index
    int next_job = 0;

    // priority queue of type worker, and use std::greater to sort by least.
    priority_queue<
    Worker,
    vector<Worker>,
    std::greater<Worker>
    > wq;

    // populate queue with our workers
    for (int i = 0; i < num_workers_; i++) {
      Worker worker_;
      worker_.next_free_time = 0;
      worker_.i = i;
      wq.push(worker_);
    }

    while (!pq.empty()) {

      // get highest priority from the queue
      Worker temp = wq.top();
      wq.pop();

      // add information to output
      assigned_workers_[next_job] = temp.i;
      start_times_[next_job++] = temp.next_free_time;

      // update the next free time
      temp.next_free_time += pq.front();
      pq.pop();
      wq.push(temp);
    }
  }

  void WriteResponse() const {
    for (int i = 0; i < assigned_workers_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}