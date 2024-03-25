#include <iostream>
#include <vector>
#include <random>
#include <numeric>

double generate_exponential_random(double rate) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::exponential_distribution<double> exp_dist(rate);
    return exp_dist(gen);
}

std::vector<double> simulate_queue(double arrival_rate, double service_rate, int num_customers) {
    std::vector<double> inter_arrival_times;
    std::vector<double> service_times;
    std::vector<double> arrival_times;
    std::vector<double> service_starts;
    std::vector<double> waiting_times;

    inter_arrival_times.reserve(num_customers);
    service_times.reserve(num_customers);
    arrival_times.reserve(num_customers);
    service_starts.reserve(num_customers);
    waiting_times.reserve(num_customers);

    double time = 0.0;
    for (int i = 0; i < num_customers; i++) {
        double inter_arrival_time = generate_exponential_random(arrival_rate);
        double service_time = generate_exponential_random(service_rate);
        double arrival_time = time + inter_arrival_time;
        double service_start_time = std::max(arrival_time, (i == 0) ? 0.0 : service_starts[i-1]);
        double waiting_time = service_start_time - arrival_time;

        inter_arrival_times.push_back(inter_arrival_time);
        service_times.push_back(service_time);
        arrival_times.push_back(arrival_time);
        service_starts.push_back(service_start_time);
        waiting_times.push_back(waiting_time);

        time = arrival_time;
    }

    double avg_waiting_time = std::accumulate(waiting_times.begin(), waiting_times.end(), 0.0) / num_customers;
    double total_waiting_time = std::accumulate(waiting_times.begin(), waiting_times.end(), 0.0);

    std::vector<double> results = {avg_waiting_time, total_waiting_time};
    return results;
}

int main() {
    double arrival_rate = 2.0 / 3.0;
    double service_rate = 4.0 / 3.0;
    std::vector<int> num_customers_list = {1000, 2000, 5000};

    for (int num_customers : num_customers_list) {
        auto results = simulate_queue(arrival_rate, service_rate, num_customers);
        std::cout << "For " << num_customers << " customers:" << std::endl;
        std::cout << "Average waiting time per customer: " << results[0] << std::endl;
        std::cout << "Total waiting time of all customers: " << results[1] << std::endl << std::endl;
    }

    arrival_rate = 4.0 / 3.0;
    service_rate = 2.0 / 3.0;
    int num_customers = 1000;

    auto results = simulate_queue(arrival_rate, service_rate, num_customers);
    std::cout << "For " << num_customers << " customers:" << std::endl;
    std::cout << "Average waiting time per customer: " << results[0] << std::endl;
    std::cout << "Total waiting time of all customers: " << results[1] << std::endl;

    return 0;
}

