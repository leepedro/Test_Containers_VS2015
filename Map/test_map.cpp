#include <map>
#include <string>

class Order
{
public:
	Order(void) = delete;
	Order(unsigned long long order_id, const std::string &product_name) : order_id_(order_id), product_name_(product_name) {}
	Order(const Order &src) : order_id_(src.order_id_), product_name_(src.product_name_), quantity_(src.quantity_) {}
	Order(Order &&src) : order_id_(src.order_id_), product_name_(std::move(src.product_name_)), quantity_(src.quantity_) {}

	const unsigned long long &order_id = this->order_id_;

	void set_quantity(long long quantity) { this->quantity_ = quantity; }

private:
	unsigned long long order_id_;
	std::string product_name_;
	long long quantity_ = 0;
};

class Customer
{
public:
	Customer(void) = default;
	Customer(const Customer &src) : orders_(src.orders_) {}
	Customer(Customer &&src) : orders_(std::move(src.orders_)) {}

	const std::map<unsigned long long, Order> &orders = this->orders_;

	void create_order(Order &&order) { this->orders_.emplace(std::make_pair(order.order_id, order)); }
	void add_order(const Order &order) { this->orders_.emplace(std::make_pair(order.order_id, order)); }

private:
	std::map<unsigned long long, Order> orders_;
};

void test_complex(void)
{
	Customer bob;

	bob.create_order(Order(1, "A"));

	Order order_2(2, "B");
	order_2.set_quantity(10);
	bob.add_order(order_2);		// A new member is created within the map.
	order_2.set_quantity(15);	// This does not affect the member of the map because they are independent now.

	auto &order_1_read_only = bob.orders.find(1)->second;
}

void test_simple(void)
{
	std::map<std::string, int> attending_record = { {"Bob", 3}, {"Mary", 2}, {"John", 4} };

	// Add a new member.
	attending_record.emplace(std::make_pair("Pedro", 1));

	// The order of entries is resorted at each new insert.

	// Operator[] returns T&, so it can be used to access values directly.
	attending_record["Bob"] = 4;
	attending_record["Mary"]++;
}

int main(void)
{
	test_simple();
	test_complex();
	return 0;
}