#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "stack.h"
#include "queue.h"
#include "bst.h"

void printVec(const std::vector<int>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i];
        if (i + 1 < v.size()) std::cout << " ";
    }
    std::cout << std::endl;
}

int main() {
    Stack<int> s;
    Queue<int> q;
    BST<int> t;
    std::string line;

    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;

        if (cmd == "exit") break;

        if (cmd == "help") {
            std::cout << "Stack commands:" << std::endl;
            std::cout << "  spush <val>" << std::endl;
            std::cout << "  spop" << std::endl;
            std::cout << "  stop" << std::endl;
            std::cout << "  speek <n>" << std::endl;
            std::cout << "  sreverse" << std::endl;
            std::cout << "  sclear" << std::endl;
            std::cout << "  ssize" << std::endl;
            std::cout << "  sprint" << std::endl;
            std::cout << std::endl;
            std::cout << "Queue commands:" << std::endl;
            std::cout << "  qpush <val>" << std::endl;
            std::cout << "  qpop" << std::endl;
            std::cout << "  qfront" << std::endl;
            std::cout << "  qback" << std::endl;
            std::cout << "  qpeek <n>" << std::endl;
            std::cout << "  qrotate <k>" << std::endl;
            std::cout << "  qclear" << std::endl;
            std::cout << "  qsize" << std::endl;
            std::cout << "  qprint" << std::endl;
            std::cout << std::endl;
            std::cout << "Tree commands:" << std::endl;
            std::cout << "  tinsert <val>" << std::endl;
            std::cout << "  tremove <val>" << std::endl;
            std::cout << "  tsearch <val>" << std::endl;
            std::cout << "  tmin" << std::endl;
            std::cout << "  tmax" << std::endl;
            std::cout << "  theight" << std::endl;
            std::cout << "  tsize" << std::endl;
            std::cout << "  tclear" << std::endl;
            std::cout << std::endl;
            std::cout << "exit - exit program" << std::endl;
            std::cout << "help - command list" << std::endl;
            continue; 
        }

        if (cmd == "spush") {
            int val;
            if (ss >> val) s.push(val);
        } else if (cmd == "spop") {
            try { std::cout << s.pop() << std::endl; }
            catch (const std::exception& e) { std::cout << e.what() << std::endl; }
        } else if (cmd == "stop") {
            try { std::cout << s.top() << std::endl; }
            catch (const std::exception& e) { std::cout << e.what() << std::endl; }
        } else if (cmd == "speek") {
            int n;
            if (ss >> n) {
                auto res = s.peekN(n);
                if (res) std::cout << *res << std::endl;
                else std::cout << "Index out of range" << std::endl;
            }
        } else if (cmd == "sreverse") {
            s.reverse();
        } else if (cmd == "sclear") {
            s.clear();
        } else if (cmd == "ssize") {
            std::cout << s.size() << std::endl;
        } else if (cmd == "sprint") {
            Stack<int> temp;
            while (!s.isEmpty()) {
                temp.push(s.pop());
            }
            while (!temp.isEmpty()) {
                int val = temp.pop();
                std::cout << val << " ";
                s.push(val);
            }
            std::cout << std::endl;
        }

        else if (cmd == "qpush") {
            int val;
            if (ss >> val) q.enqueue(val);
        } else if (cmd == "qpop") {
            try { std::cout << q.dequeue() << std::endl; }
            catch (const std::exception& e) { std::cout << e.what() << std::endl; }
        } else if (cmd == "qfront") {
            try { std::cout << q.front() << std::endl; }
            catch (const std::exception& e) { std::cout << e.what() << std::endl; }
        } else if (cmd == "qback") {
            try { std::cout << q.back() << std::endl; }
            catch (const std::exception& e) { std::cout << e.what() << std::endl; }
        } else if (cmd == "qpeek") {
            int n;
            if (ss >> n) {
                auto res = q.peekN(n);
                if (res) std::cout << *res << std::endl;
                else std::cout << "Index out of range" << std::endl;
            }
        } else if (cmd == "qrotate") {
            int k;
            if (ss >> k) q.rotate(k);
        } else if (cmd == "qclear") {
            q.clear();
        } else if (cmd == "qsize") {
            std::cout << q.size() << std::endl;
        } else if (cmd == "qprint") {
            Queue<int> temp;
            while (!q.isEmpty()) {
                int val = q.dequeue();
                std::cout << val << " ";
                temp.enqueue(val);
            }
            std::cout << std::endl;
            while (!temp.isEmpty()) {
                q.enqueue(temp.dequeue());
            }
        }

        else if (cmd == "tinsert") {
            int val;
            if (ss >> val) t.insert(val);
        } else if (cmd == "tremove") {
            int val;
            if (ss >> val) t.remove(val);
        } else if (cmd == "tsearch") {
            int val;
            if (ss >> val) {
                std::cout << (t.search(val) ? "Found" : "Not found") << std::endl;
            }
        } else if (cmd == "tinorder") {
            printVec(t.inorderRecursive());
        } else if (cmd == "tpreorder") {
            printVec(t.preorderRecursive());
        } else if (cmd == "tpostorder") {
            printVec(t.postorderRecursive());
        } else if (cmd == "tmin") {
            auto res = t.min();
            if (res) std::cout << *res << std::endl;
            else std::cout << "Tree is empty" << std::endl;
        } else if (cmd == "tmax") {
            auto res = t.max();
            if (res) std::cout << *res << std::endl;
            else std::cout << "Tree is empty" << std::endl;
        } else if (cmd == "theight") {
            std::cout << t.height() << std::endl;
        } else if (cmd == "tsize") {
            std::cout << t.size() << std::endl;
        } else if (cmd == "tclear") {
            t.clear();
        } 
    }
    return 0;
}