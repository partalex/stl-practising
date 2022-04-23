#include<algorithm>
#include<iostream>
#include<vector>
#include<array>
#include<functional>
#include<numeric>
#include<string>
#include<string_view>
#include<ranges>
#include<cstddef>
#include<iterator>
#include<iomanip>
#include<thread>
#include<random>
using namespace std;

// fill vector with random values
vector<int> v{ 2, 4, 7, 8, 3, 6, 9, 8, 1, 0, 5 };

int main()
{
	// std::all_of, std::none_of, std::any_of // C++ 11
	/*
	{
		// all_of
		cout << "all_of" << "\n";

		{
			if (all_of(v.cbegin(), v.cend(), [](int i) { return i % 2 == 0; }))
				cout << "All numbers are even." << "\n";
			else
				cout << "Not all numbers are even." << "\n";
		}

		// none_of
		cout << "none_of" << "\n";

		{
			if (std::none_of(v.cbegin(), v.cend(),
				std::bind(std::modulus<>(), std::placeholders::_1, 2)))
				std::cout << "None of them are odd." << "\n";
			else 	std::cout << "Some of them are odd." << "\n";
		}

		// any_of
		cout << "any_of" << "\n";

		{
			if (std::any_of(v.cbegin(), v.cend(),
				[](auto& i) {
					if (i % 2) return true;
				}
			))
				std::cout << "At least one number is divisible by 7." << "\n";
		}
	}
	//*/

	// std::ranges::all_of, std::ranges::any_of, std::ranges::none_of // c++20
	// treba skontati cemu sluzi ovaj poslednji argument, ne znam sta je ovo
	/*
	{
		std::cout << "Among the numbers: ";
		ranges::copy(v, std::ostream_iterator<int&>(std::cout, " "));
		std::cout << '\n';

		if (ranges::all_of(v.cbegin(), v.cend(), [](int i) { return i % 2 == 0; })) {
			std::cout << "All numbers are even." << "\n";
		}
		if (ranges::none_of(v, std::bind(std::modulus<int>(), std::placeholders::_1, 2))) {
			std::cout << "None of them are odd." << "\n";
		}

		auto DivisibleBy = [](int d)
		{
			return [d](int m) { return m % d == 0; };
		};

		if (ranges::any_of(v, DivisibleBy(7))) {
			std::cout << "At least one number is divisible by 7." << "\n";
		}
	}
	//*/

	// std::for_each, std::for_each_n
	/*
	{
		// std::for_each
		auto inc = [](int& n) { n++; };
		std::for_each(v.begin(), v.end(), inc);
		std::for_each(v.begin(), v.end(), [](auto& t) {cout << t << " "; });

		// std::for_each
		std::for_each_n(v.begin(), 5, inc);
		std::for_each(v.begin(), v.end(), [](auto& t) {cout << t << " "; });
	}
	//*/

	// std::ranges::for_each // C++20
	/*
	{
		auto print = [](const auto& n) { std::cout << n << ' '; };
		std::ranges::for_each(v, print); // samo je ovo novo, osto se ponasa kao stari std::for_each
	}
	//*/

	//  std::ranges::for_each_n // C++20
	/*
	{
		struct ex {
			int first;
			int second;
		};
		vector<ex> v{ { 1, 2 }, { 3, 4 }, { 5, 6 } };
		std::ranges::for_each_n(v.begin(), 3, [](auto& n) { n *= -1; }, &ex::first);
		for (auto& i : v)
			cout << i.first << " " << i.second << "\n";

	}
	//*/

	// std::count, std::count_if
	/*
	{
		std::copy(v.cbegin(), v.cend(), std::ostream_iterator<int>(std::cout, " "));
		cout << "\n";

		// std::count
		for (const int target : {3, 4, 5}) {
			const int num_items = std::count(v.cbegin(), v.cend(), target);
			std::cout << "number: " << target << ", count: " << num_items << '\n';
		}

		// std::count_if
		int count_div4 = std::count_if(v.begin(), v.end(), [](int i) {return i % 4 == 0; });
		std::cout << "numbers divisible by four: " << count_div4 << '\n';
	}
	//*/

	// std::ranges::count, std::ranges::count_if // C++20
	/*
	{
		auto number_of_fives = std::ranges::count(v, 5);
		//auto number_of_fives = std::ranges::count(v.begin(), v.end(), 5); // old way
		int number_of_threes = std::ranges::count_if(v, [](int i) {return i % 3 == 0; });
		//int number_of_threes = std::ranges::count_if(v.begin(), v.end(), [](int i) {return i % 3 == 0; }); // old way
	}
	//*/

	// mismatch
	/*
	{
		//string koka = "abcdfabc";
		//auto mis = mismatch(koka.begin(), koka.end(), "abc");
		//cout << "first mismatch: " << *mis.first << " " << *mis.second << "\n";

		vector<int>a = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		vector<int>b = { 1, 2, 3, 4, 5 };
		int myints[] = { 1, 2, 4, 6 };
		auto mis = mismatch(a.begin(), a.end(), myints);
		cout << "first mismatch: " << *mis.first << " " << *mis.second << "\n";

		// ovo nesto ne radi
		//auto koka = mismatch(a.begin(), a.end(), b.begin(), std::equal_to<int>());
		//cout << "first mismatch: " << *koka.first << " " << *koka.second << "\n";
	}
	//*/

	// std::ranges::mismatch  C++11
	// ako ne postoji mismatch onda ispis puca, ne znam kako da proverim da li je res mismatch-a prazan
	/*
	{
		string_view in1{ "radarXxradar" };
		const auto res1 = std::ranges::mismatch(in1, in1 | std::views::reverse);
		cout << "first mismatch: " << *res1.in1 << " " << *res1.in2 << '\n';

		string_view in2{ "radarXYZxradar" };
		const auto res2 = std::ranges::mismatch(
			in2,
			in2 | std::views::reverse,
			[](char c1, char c2) { return std::toupper(c1) == std::toupper(c2); }
			// ovde ce da prvo uveca malo x pa ce da X == X da bude true
		);
		cout << "first mismatch: " << *res2.in1 << " " << *res2.in2 << '\n';

		vector<int> t1{ 1,2,3,4 };
		vector<int> t2{ 1,2,4,5 };

		auto in3 = std::ranges::mismatch(
			t1,
			t2,
			std::equal_to<int>()
		);
		cout << "first mismatch: " << *in3.in1 << " " << *in3.in2 << '\n';

	}
	//*/

	// std::find, std::find_if, std::find_if_not
	/*
	{
		std::vector<int> v{ 1, 2, 3, 4 };
		int n1 = 3;
		int n2 = 5;
		auto is_even = [](int i) { return i % 2 == 0; };

		auto result1 = std::find(begin(v), end(v), n1);
		auto result2 = std::find(begin(v), end(v), n2);
		auto result3 = std::find_if(begin(v), end(v), is_even);

		(result1 != std::end(v))
			? std::cout << "v contains " << n1 << '\n'
			: std::cout << "v does not contain " << n1 << '\n';

		(result2 != std::end(v))
			? std::cout << "v contains " << n2 << '\n'
			: std::cout << "v does not contain " << n2 << '\n';

		(result3 != std::end(v))
			? std::cout << "v contains an even number: " << *result3 << '\n'
			: std::cout << "v does not contain even numbers\n";
	}
	//*/


	// std::ranges::find, std::ranges::find_if, std::ranges::find_if_not C++20
	/*
	{
		namespace ranges = std::ranges;

		const int n1 = 3;
		const int n2 = 5;
		const auto v = { 4, 1, 3, 2 };

		if (ranges::find(v, n1) != v.end())
			std::cout << "v contains: " << n1 << '\n';
		else
			std::cout << "v does not contain: " << n1 << '\n';

		if (ranges::find(v.begin(), v.end(), n2) != v.end())
			std::cout << "v contains: " << n2 << '\n';
		else
			std::cout << "v does not contain: " << n2 << '\n';

		auto is_even = [](int x) { return x % 2 == 0; };

		if (auto result = ranges::find_if(v.begin(), v.end(), is_even); result != v.end())
			std::cout << "First even element in v: " << *result << '\n';
		else
			std::cout << "No even elements in v\n";

		if (auto result = ranges::find_if_not(v, is_even); result != v.end())
			std::cout << "First odd element in v: " << *result << '\n';
		else
			std::cout << "No odd elements in v\n";

		auto divides_13 = [](int x) { return x % 13 == 0; };

		if (auto result = ranges::find_if(v, divides_13); result != v.end())
			std::cout << "First element divisible by 13 in v: " << *result << '\n';
		else
			std::cout << "No elements in v are divisible by 13\n";

		if (auto result = ranges::find_if_not(v.begin(), v.end(), divides_13); result != v.end())
			std::cout << "First element indivisible by 13 in v: " << *result << '\n';
		else
			std::cout << "All elements in v are divisible by 13\n";
	}
	//*/

	// std::find_end
	// poslednje ponavaljanje subkolekcije u kolekciji
	/*
	{
		std::vector<int> v{ 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4 };
		std::vector<int>::iterator result;

		auto check = [&] {
			result == v.end()
				? std::cout << "sequence not found\n"
				: std::cout << "last occurrence is at: "
				<< std::distance(v.begin(), result) << "\n";
		};

		std::vector<int> t1{ 1, 2, 3 };
		result = std::find_end(v.begin(), v.end(), t1.begin(), t1.end());
		check();

		std::vector<int> t2{ 4, 5, 6 };
		result = std::find_end(v.begin(), v.end(), t2.begin(), t2.end());
		check();
	}
	//*/

	// std::ranges::find_end
	/*
	{
		auto print = [](const auto haystack, const auto needle)
		{
			const auto pos = std::distance(haystack.begin(), needle.begin());
			std::cout << "In \"";
			for (const auto c : haystack) { std::cout << c; }
			std::cout << "\" found \"";
			for (const auto c : needle) { std::cout << c; }
			std::cout << "\" at position [" << pos << ".." << pos + needle.size() << ")\n"
				<< std::string(4 + pos, ' ') << std::string(needle.size(), '^') << '\n';
		};

		using namespace std::literals;
		constexpr auto secret{ "password password word..."sv };
		constexpr auto wanted{ "password"sv };

		constexpr auto found1 = std::ranges::find_end(
			secret.cbegin(), secret.cend(), wanted.cbegin(), wanted.cend());
		print(secret, found1);

		constexpr auto found2 = std::ranges::find_end(secret, "word"sv);
		print(secret, found2);

		const auto found3 = std::ranges::find_end(secret, "ORD"sv,
			[](const char x, const char y) { // uses a binary predicate
				return std::tolower(x) == std::tolower(y);
			});
		print(secret, found3);

		const auto found4 = std::ranges::find_end(secret, "SWORD"sv, {}, {},
			[](char c) { return std::tolower(c); }); // projects the 2nd range
		print(secret, found4);

		static_assert(std::ranges::find_end(secret, "PASS"sv).empty()); // => not found

	}
	//*/

	// std::find_first_of
	/*
	{
		const std::vector<int> v{ 0, 3, 25, 5 };
		const auto t1 = { 19, 10, 5, 6, 3, 4 };

		auto res = std::find_first_of(
			v.begin(),
			v.end(),
			t1.begin(),
			t1.end()
			//,[](int x, int y) { return x % y == 0; }
		);
		// print res dsitance and refference
		std::cout << "first of: " << *res << '\n';
		std::cout << "distance: " << std::distance(v.begin(), res) << '\n';
	}
	//*/

	// std::ranges::find_first_of C++20
	// primer sa cppreference-a nesto nece da se prevede
	// poenta da se svi range-evi razlikuju sto mogu da uhvate celu kolekcinju; ne zattevaju begin end
	/*
	{
	}
	//*/

	// std::adjacent_find
	/*
	{
		std::vector<int> v1{ 0, 1, 2, 3, 40, 40, 41, 41, 5 };
		auto i1 = std::adjacent_find(v1.begin(), v1.end()
			//, std::bind(std::modulus<>(), std::placeholders::_1, 2) // moze i ovo da se stavi
		);

		if (i1 == v1.end())
			std::cout << "No matching adjacent elements\n";
		else
			std::cout << "The first adjacent pair of equal elements is at "
			<< std::distance(v1.begin(), i1) << ", *i1 = "
			<< *i1 << '\n';

		auto i2 = std::adjacent_find(v1.begin(), v1.end(), std::greater<int>());
		if (i2 == v1.end())
			std::cout << "The entire vector is sorted in ascending order\n";
		else
			std::cout << "The last element in the non-decreasing subsequence is at "
			<< std::distance(v1.begin(), i2) << ", *i2 = " << *i2 << '\n';
	}
	//*/

	// std::ranges::adjacent_find
	/*
	{
		std::vector<int> v1{ 0, 1, 2, 3, 40, 40, 41, 41, 5 };
		namespace ranges = std::ranges;

		auto i1 = ranges::adjacent_find(v1.begin(), v1.end());
		if (i1 == v1.end())
			std::cout << "No matching adjacent elements\n";
		else
			std::cout << "The first adjacent pair of equal elements is at ["
			<< ranges::distance(v1.begin(), i1) << "] == " << *i1 << '\n';

		auto i2 = ranges::adjacent_find(v1, ranges::greater());
		if (i2 == v1.end())
			std::cout << "The entire vector is sorted in ascending order\n";
		else
			std::cout << "The last element in the non-decreasing subsequence is at ["
			<< ranges::distance(v1.begin(), i2) << "] == " << *i2 << '\n';
	}
	//*/

	// std::search
	// return iterataton gde ga je nasao
	/*
	{
		std::string cont{ "why waste time learning, when ignorance is instantaneous?" };
		string s{ "learning" };
		auto res1 = std::search(cont.begin(), cont.end(), s.begin(), s.end()) != cont.end();
		res1
			? cout << "nasao"
			: cout << "nije nasao"
			;
	}
	//*/

	// std::ranges::search C+20
	// ovo je neki glup primer
	/*
	{
		constexpr auto haystack{ "abcd abcdf"sv };
		constexpr auto needle{ "bcd"sv };

		// the search uses iterator pairs begin()/end():
		constexpr auto found1 = std::ranges::search(
			haystack.begin(), haystack.end(),
			needle.begin(), needle.end());

		constexpr auto found2 = std::ranges::search(haystack, needle);

		cout << found2.data() << "\n";
	}
	//*/

	// std::search_n
	// trazi n rednih elemenata koji su jednak zadatoj vrednosti
	/*
	{
		const char sequence[] = "1001010100010101001010101";
		std::cout << std::boolalpha;

		int count = 4;
		auto res = std::search_n(std::begin(sequence), std::end(sequence), count, '0') != std::end(sequence);
		std::cout << "Has " << count << " consecutive zeros : " << res << "\n";

		count = 3;
		res = std::search_n(std::begin(sequence), std::end(sequence), count, '0') != std::end(sequence);
		std::cout << "Has " << count << " consecutive zeros : " << res << "\n";

	}
	//*/

	// std::ranges::search_n
	/*
	{
		auto nums = { 1, 2, 2, 3, 4, 1, 2, 2, 2, 1, 2, 2, 2, };
		constexpr int count{ 3 };
		constexpr int value{ 2 };

		auto
			res = std::ranges::search_n(
				nums,
				count,
				value
			);

		cout << res.size() << "\n";
		cout << std::distance(nums.begin(), res.begin()) << "\n";

		res = std::ranges::search_n(
			res.end(),
			nums.end(),
			count,
			value
		);

		cout << res.size() << "\n";
		cout << std::distance(nums.begin(), res.begin()) << "\n";

	}
	//*/

	// std::ranges::starts_with C++23
	// ovo je nesto komplikovano
	// u sustini je kako pocinje string, ali su primeru uzasno glupi i nelogicni
	/*
	{
		using namespace std::literals;
		constexpr auto ascii_upper = [](char8_t c)
		{
			return u8'a' <= c && c <= u8'z' ? static_cast<char8_t>(c + u8'A' - u8'a') : c;
		};

		constexpr auto cmp_ignore_case = [=](char8_t x, char8_t y)
		{
			return ascii_upper(x) == ascii_upper(y);
		};

		static_assert(std::ranges::starts_with("const_cast", "const"sv));
		static_assert(std::ranges::starts_with("constexpr", "const"sv));
		static_assert(!std::ranges::starts_with("volatile", "const"sv));

		std::cout
			<< std::boolalpha
			<< std::ranges::starts_with(u8"Constantinopolis", u8"constant"sv,
				{}, ascii_upper, ascii_upper) << ' '
			<< std::ranges::starts_with(u8"Istanbul", u8"constant"sv,
				{}, ascii_upper, ascii_upper) << ' '
			<< std::ranges::starts_with(u8"Metropolis", u8"metro"sv,
				cmp_ignore_case) << ' '
			<< std::ranges::starts_with(u8"Acropolis", u8"metro"sv,
				cmp_ignore_case) << '\n';

		constexpr static auto v = { 1, 3, 5, 7, 9 };
		constexpr auto odd = [](int x) { return x % 2; };

		auto res =
			std::ranges::starts_with(v,
				std::views::iota(1) | std::views::filter(odd) | std::views::take(3));

	}
	//*/

	// std::ranges::ends_with C++23
	// kako se zavrsava string
	/*
	{
		std::cout
			<< std::boolalpha
			<< std::ranges::ends_with("static_cast", "cast") << '\n' // true
			<< std::ranges::ends_with("const_cast", "cast") << '\n' // true
			<< std::ranges::ends_with("reinterpret_cast", "cast") << '\n' // true
			<< std::ranges::ends_with("dynamic_cast", "cast") << '\n' // true
			<< std::ranges::ends_with("move", "cast") << '\n' // false
			<< std::ranges::ends_with("move_if_noexcept", "cast") << '\n' // false
			<< std::ranges::ends_with("forward", "cast") << '\n'; // false
		static_assert(
			!std::ranges::ends_with("as_const", "cast") and
			!!std::ranges::ends_with("bit_cast", "cast") and
			!std::ranges::ends_with("to_underlying", "cast") and
			!!std::ranges::ends_with(std::array{ 1,2,3,4 }, std::array{ 3,4 }) and
			!std::ranges::ends_with(std::array{ 1,2,3,4 }, std::array{ 4,5 })
			);
	}
	//*/

	// std::copy, std::copy_if C++11
	/*
	{
		std::vector<int> from_vector(10);
		std::iota(from_vector.begin(), from_vector.end(), 0);

		std::vector<int> to_vector;
		std::copy(from_vector.begin(), from_vector.end(),
			std::back_inserter(to_vector));
		// or, alternatively,
		//  std::vector<int> to_vector(from_vector.size());
		//  std::copy(from_vector.begin(), from_vector.end(), to_vector.begin());
		// either way is equivalent to
		//  std::vector<int> to_vector = from_vector;

		std::cout << "to_vector contains: ";

		std::copy(to_vector.begin(), to_vector.end(),
			std::ostream_iterator<int>(std::cout, " "));
		std::cout << '\n';

		std::cout << "odd numbers in to_vector are: ";

		std::copy_if(to_vector.begin(), to_vector.end(),
			std::ostream_iterator<int>(std::cout, " "),
			[](int x) { return x % 2 != 0; });
		std::cout << '\n';

		std::cout << "to_vector contains these multiples of 3:\n";

		to_vector.clear();
		std::copy_if(from_vector.begin(), from_vector.end(),
			std::back_inserter(to_vector),
			[](int x) { return x % 3 == 0; });

		for (int x : to_vector)
			std::cout << x << ' ';
	}
	//*/

	// std::ranges::copy, std::ranges::copy_if, std::ranges::copy_result, std::ranges::copy_if_result C++20
	/*
	{
		std::vector<int> from_vector(10);
		std::iota(from_vector.begin(), from_vector.end(), 0);

		std::vector<int> to_vector;

		namespace ranges = std::ranges;
		ranges::copy(from_vector.begin(), from_vector.end(),
			std::back_inserter(to_vector));
		// or, alternatively,
		//  std::vector<int> to_vector(from_vector.size());
		//  ranges::copy(from_vector.begin(), from_vector.end(), to_vector.begin());
		// either way is equivalent to
		//  std::vector<int> to_vector = from_vector;

		std::cout << "to_vector contains: ";

		ranges::copy(to_vector, std::ostream_iterator<int>(std::cout, " "));
		std::cout << '\n';

		std::cout << "odd numbers in to_vector are: ";

		ranges::copy_if(to_vector, std::ostream_iterator<int>(std::cout, " "),
			[](int x) { return (x % 2) == 1; });
		std::cout << '\n';
	}
	//*/

	// std::copy_n C++11
	/*
	{
		std::string in = "1234567890";
		std::string out;

		std::copy_n(in.begin(), 4, std::back_inserter(out));
		std::cout << out << '\n';

		std::vector<int> v_in(128);
		std::iota(v_in.begin(), v_in.end(), 1);
		std::vector<int> v_out(v_in.size());

		std::copy_n(v_in.cbegin(), 100, v_out.begin());
		std::cout << std::accumulate(v_out.begin(), v_out.end(), 0) << '\n';
	}
	//*/

	// std::ranges::copy_n, std::ranges::copy_n_result
	/*
	{
		const std::string_view in{ "ABCDEFGH" };
		std::string out;

		std::ranges::copy_n(in.begin(), 4, std::back_inserter(out));
		std::cout << std::quoted(out) << '\n';

		out = "abcdefgh";
		const auto res = std::ranges::copy_n(in.begin(), 5, out.begin());
		std::cout
			<< "*(res.in): '" << *(res.in) << "', distance: "
			<< std::distance(std::begin(in), res.in) << '\n'
			<< "*(res.out): '" << *(res.out) << "', distance: "
			<< std::distance(std::begin(out), res.out) << '\n';
		}
	//*/

	// std::copy_backward
	// ako se kopira nedovoljan broj elemenata onda se nalepi posledji elem na prazna mesta
	/*
	{
		std::vector<int> from_vector;
		for (int i = 0; i < 10; i++)
			from_vector.push_back(i);

		std::vector<int> to_vector(15);
		std::copy_backward(from_vector.begin(), from_vector.end(), to_vector.end());

		std::cout << "to_vector contains: ";
		for (auto i : to_vector)
			std::cout << i << " ";
	}
	//*/

	// std::ranges::copy_backward, std::ranges::copy_backward_result C++20
	/*
	{
		auto print = [](std::string_view rem, std::ranges::forward_range auto const& r) {
			for (std::cout << rem << ": "; auto const& elem : r)
				std::cout << elem << ' ';
			std::cout << '\n';
		};

		const auto src = { 1, 2, 3, 4 };
		print("src", src);

		std::vector<int> dst(src.size() + 2);
		std::ranges::copy_backward(src, dst.end());
		print("dst", dst);

		std::ranges::fill(dst, 0);
		const auto [in, out] =
			std::ranges::copy_backward(src.begin(), src.end() - 2, dst.end());
		print("dst", dst);

		std::cout
			<< "(in - src.begin) == " << std::distance(src.begin(), in) << '\n'
			<< "(out - dst.begin) == " << std::distance(dst.begin(), out) << '\n';
	}
	//*/

	// std::move
	/*
	{
		auto f = [](int n)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(n));
			std::cout << "thread " << n << " ended" << std::endl;
		};

		std::vector<std::thread> v;
		v.emplace_back(f, 250);
		v.emplace_back(f, 500);
		v.emplace_back(f, 750);
		std::list<std::thread> l;

		// copy() would not compile, because std::thread is noncopyable
		std::move(v.begin(), v.end(), std::back_inserter(l));
		for (auto& t : l) t.join();
	}
	//*/

	// std::ranges::move, std::ranges::move_result C++20
	/*
	{
		using namespace std::literals::chrono_literals;

		auto f = [](std::chrono::milliseconds n)
		{
			std::this_thread::sleep_for(n);
			std::cout << "thread with n=" << n.count() << "ms ended" << std::endl;
		};

		std::vector<std::jthread> v;
		v.emplace_back(f, 400ms);
		v.emplace_back(f, 600ms);
		v.emplace_back(f, 800ms);

		std::list<std::jthread> l;

		// std::ranges::copy() would not compile, because std::jthread is non-copyable
		std::ranges::move(v, std::back_inserter(l));
	}
	//*/

	// std::move_backward C++11
	/*
	{
		using container = std::vector<std::string>;

		auto print = [](std::string_view comment, const container& src, const container& dst = {})
		{
			auto prn = [](std::string_view name, const container& cont) {
				std::cout << name;
				for (const auto& s : cont) { std::cout << (s.empty() ? "*" : s.data()) << ' '; }
				std::cout << '\n';
			};
			std::cout << comment << '\n';
			prn("src: ", src);
			if (dst.empty()) return;
			prn("dst: ", dst);
		};

		container src{ "foo", "bar", "baz" };
		container dst{ "qux", "quux", "quuz", "corge" };
		print("Non-overlapping case; before move_backward:", src, dst);
		std::move_backward(src.begin(), src.end(), dst.end());
		print("After:", src, dst);

		src = { "snap", "crackle", "pop", "lock", "drop" };
		print("Overlapping case; before move_backward:", src);
		std::move_backward(src.begin(), std::next(src.begin(), 3), src.end());
		print("After:", src);
	}
	//*/

	// std::ranges::move_backward, std::ranges::move_backward_result C++20
	// isto kao i ovo gore; stoga nista nije napisano nista	
	/*
	{
	}
	//*/

	// std::fill
	/*
	{
		std::vector<int> v{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		std::fill(v.begin(), v.end(), -1);
		for (auto& elem : v)
			std::cout << elem << " ";
		std::cout << "\n";
	}
	//*/

	// std::ranges::fill C++20
	/*
	{
		std::vector<int> v{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		namespace ranges = std::ranges;
		ranges::fill(v.begin(), v.end(), -1);
		for (auto& elem : v)
			std::cout << elem << " ";
		std::cout << "\n";

		ranges::fill(v, 10);
		for (auto& elem : v)
			std::cout << elem << " ";
		std::cout << "\n";
	}
	//*/

	// std::fill_n	
	/*
	{
		std::vector<int> v1{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		std::fill_n(v1.begin(), 5, -1);
		std::copy(begin(v1), end(v1), std::ostream_iterator<int>(std::cout, " "));
		std::cout << '\n';
	}
	//*/

	// std::ranges::fill_n C++20
	/*
	{
		constexpr auto n{ 8 };
		std::vector<std::string> v(n, "*");
		std::ranges::fill_n(v.begin(), n, "8");
	}
	//*/

	// std::transform
	// applies a function to a range of elements, storing results in a destination range
	/*
	{
		std::string s("hello");
		std::transform(s.begin(), s.end(), s.begin(),
			[](unsigned char c) -> unsigned char { return std::toupper(c); });

		std::vector<std::size_t> ordinals;
		std::transform(s.begin(), s.end(), std::back_inserter(ordinals),
			[](unsigned char c) -> std::size_t { return c; });

		std::cout << s << ':';
		for (auto ord : ordinals) {
			std::cout << ' ' << ord;
		}

		std::transform(ordinals.cbegin(), ordinals.cend(), ordinals.cbegin(),
			ordinals.begin(), std::plus<>{});

		std::cout << '\n';
		for (auto ord : ordinals) {
			std::cout << ord << ' ';
		}
		std::cout << '\n';
	}
	//*/

	// std::ranges::transform, std::ranges::unary_transform_result, std::ranges::binary_transform_result C++20
	// applies a function to a range of elements
	/*
	{
		std::string s("hello");
		namespace ranges = std::ranges;
		ranges::transform(s.begin(), s.end(), s.begin(),
			[](unsigned char c) -> unsigned char { return std::toupper(c); });

		std::vector<std::size_t> ordinals;
		ranges::transform(s, std::back_inserter(ordinals),
			[](unsigned char c) -> std::size_t { return c; });

		std::cout << s << ':';
		for (auto ord : ordinals)
			std::cout << ' ' << ord;

		ranges::transform(ordinals, ordinals, ordinals.begin(), std::plus{});
		// source, destination, niz koji koristi za operaciju, operacija

		std::cout << '\n';
		for (auto ord : ordinals)
			std::cout << ord << ' ';
		std::cout << '\n';

		struct Foo {
			char bar;
		};

		const std::vector<Foo> f = { {'h'},{'e'},{'l'},{'l'},{'o'} };
		std::string bar;
		ranges::transform(f, std::back_inserter(bar), &Foo::bar);
		std::cout << bar << '\n';
	}
	//*/

	// std::generate
	// assigns the results of successive function calls to every element in a range
	/*
	{
		auto f = []()
		{
			static int i;
			return ++i;
		};

		std::vector<int> v(5);
		auto print = [&] {
			for (std::cout << "v: "; auto iv: v)
				std::cout << iv << " ";
			std::cout << "\n";
		};

		std::generate(v.begin(), v.end(), f);
		print();

		// Initialize with default values 0,1,2,3,4 from a lambda function
		// Equivalent to std::iota(v.begin(), v.end(), 0);
		std::generate(v.begin(), v.end(), [n = 0]() mutable { return n++; });
		print();

	}
	//*/

	// std::ranges::generate C++20
	/*
	{
		auto dice = []() {
			static std::uniform_int_distribution<int> distr{ 1, 6 };
			static std::random_device device;
			static std::mt19937 engine{ device() };
			return distr(engine);
		};

		vector<int> koka(10);
		std::ranges::generate(koka,
			[]() {static int i = 1; return i++; }
		);

		for (auto& i : koka)
			cout << i << " ";
		cout << "\n";

		std::ranges::generate(koka, dice);
		for (auto& i : koka)
			cout << i << " ";
		cout << "\n";
	}
	//*/

	// std::generate_n
	/*
	{
		std::mt19937 rng; // default constructed, seeded with fixed seed
		std::generate_n(
			std::ostream_iterator<std::mt19937::result_type>(std::cout, " "),
			5,
			std::ref(rng));
		std::cout << '\n';
	}
	//*/

	// std::ranges::generate_n C++20
	/*
	{
		auto dice = []() {
			static std::uniform_int_distribution<int> distr{ 1, 6 };
			static std::random_device device;
			static std::mt19937 engine{ device() };
			return distr(engine);
		};

		std::array<int, 8> v;
		std::ranges::generate_n(v.begin(), v.size(), dice);
		for (auto& i : v)
			cout << i << " ";
		cout << "\n";

		std::ranges::generate_n(v.begin(), v.size(), [n{ 0 }]() mutable { return n++; });
		// same effect as std::iota(v.begin(), v.end(), 0);
		for (auto& i : v)
			cout << i << " ";
		cout << "\n";
	}
	//*/

	//std::remove, std::remove_if
	/*
	{
		std::string str1 = "Text with some   spaces";
		auto noSpaceEnd = std::remove(str1.begin(), str1.end(), ' ');

		// The spaces are removed from the string only logically.
		// Note, we use view, the original string is still not shrunk:
		std::cout << std::string_view(str1.begin(), noSpaceEnd)
			<< " size: " << str1.size() << '\n';

		str1.erase(noSpaceEnd, str1.end());

		// The spaces are removed from the string physically.
		std::cout << str1 << " size: " << str1.size() << '\n';

		std::string str2 = "Text\n with\tsome \t  whitespaces\n\n";
		str2.erase(std::remove_if(str2.begin(),
			str2.end(),
			[](unsigned char x) {return std::isspace(x); }),
			str2.end());
		std::cout << str2 << '\n';
	}
	//*/

	// std::ranges::remove, std::ranges::remove_if C++20
	///*
	{

	}
	//*/

	return 0;
}

// 
/*
{
}
//*/

