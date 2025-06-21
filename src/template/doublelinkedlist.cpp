/*==== Copyright 2025 Azruine ====*/

#include <memory>
#include <utility>

template<typename T>
class Node {
private:
    T data;
    std::weak_ptr<Node> prev;
    std::shared_ptr<Node> next;

public:
    // NOLINTNEXTLINE - clang-tidy does not recognize List initializing
    explicit Node(T&& value) : data(std::forward<T>(value)) {}
    void set_next(const std::shared_ptr<Node>& next_node) { next = next_node; }
    void set_prev(const std::weak_ptr<Node>& prev_node) { prev = prev_node; }
    void set_data(T value) { data = value; }
    [[nodiscard]] std::shared_ptr<Node> get_next() const { return next; }
    [[nodiscard]] std::weak_ptr<Node> get_prev() const { return prev; }
    [[nodiscard]] T get_data() const { return data; }
};

template<typename T>
class DoubleLinkedList {
private:
    std::shared_ptr<Node<T>> head = nullptr;
    std::shared_ptr<Node<T>> tail = nullptr;

public:
    // constructor
    DoubleLinkedList() = default;
    // destructor
    ~DoubleLinkedList() {
        if (head == nullptr) {
            return;
        }
        auto cur_node = head;
        while (cur_node != nullptr) {
            cur_node->set_next(std::shared_ptr<Node<T>>());
            cur_node->set_prev(std::weak_ptr<Node<T>>());
            cur_node = cur_node->get_next();
        }
    }
    // copy constructor
    DoubleLinkedList(DoubleLinkedList const& other) = delete;
    // copy assignment operator
    DoubleLinkedList& operator=(DoubleLinkedList const& other) = delete;
    // move constructor
    DoubleLinkedList(DoubleLinkedList&& other) = delete;
    // move assignment operator
    DoubleLinkedList& operator=(DoubleLinkedList const&& other) = delete;

    void add(T const& value) {
        if (head == nullptr) {
            head = std::make_shared<Node<T>>(value);
            head->set_prev(head);
            head->set_next(head);
            tail = head;
        } else {
            auto new_node = std::make_shared<Node<T>>(value);

            tail->set_next(new_node);
            new_node->set_prev(tail);

            head->set_prev(new_node);
            new_node->set_next(head);
            tail = new_node;
        }
    }
    void remove(T const& value) {
        if (head != nullptr) {
            bool found = false;
            auto cur_node = head;
            // NOLINTNEXTLINE - well... this is great usage for do-while loop...
            do {
                if (cur_node->get_data() == value) {
                    found = true;
                    break;
                }
                cur_node = cur_node->get_next();
            } while (cur_node != head);
            if (!found) {
                return;
            }
            if (cur_node->get_next() == cur_node) {
                head.reset();
                tail.reset();
                return;
            }
            cur_node->get_prev().lock()->set_next(cur_node->get_next());
            cur_node->get_next()->set_prev(cur_node->get_prev());
            if (cur_node == head) {
                head = cur_node->get_next();
            } else if (cur_node == tail) {
                tail = cur_node->get_prev().lock();
            }
            cur_node->set_next(std::shared_ptr<Node<T>>());
            cur_node->set_prev(std::weak_ptr<Node<T>>());
        }
    }
    [[nodiscard]] std::shared_ptr<Node<T>> get_head() const { return head; }
};
