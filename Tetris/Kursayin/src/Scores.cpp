#include "Scores.h"
#include <fstream>
#include <algorithm>
#include <iostream>
Scores::Scores(const std::string& filename)
    : filename(filename) {
			  std::ofstream ofs(filename, std::ios::app);
    // 'app' mode will create the file if missing, without overwriting
    ofs.close();

		}

std::vector<int> Scores::getTopScores(int n) const {
    std::vector<int> copy = scores;
    std::sort(copy.begin(), copy.end(), std::greater<int>());
    if (copy.size() > n) copy.resize(n);
    return copy;
}

// void Scores::load() {
//     scores.clear();
//     std::ifstream in(filename);
//     int s;
//     while (in >> s)
//         scores.push_back(s);
// }

void Scores::load() {
    scores.clear();
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "Warning: could not open " << filename << "\n";
        return;
    }
    int s;
    while (in >> s)
        scores.push_back(s);
}

void Scores::save() {
    std::ofstream out(filename);
    for (int s : scores)
        out << s << "\n";
}

void Scores::addScore(int score) {
    scores.push_back(score);
    std::sort(scores.begin(), scores.end(), std::greater<int>());

    if (scores.size() > MAX)
        scores.resize(MAX);

    save();
}

const std::vector<int>& Scores::getScores() const {
    return scores;
}
