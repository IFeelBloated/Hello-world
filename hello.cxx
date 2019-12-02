#include <iostream>
#include <array>
#include <utility>

auto main()->int {
	auto Coefficients = std::array{
		40054.22809497995, -114213.82003897215, 132446.92244138764,
		-83652.25144306717, 32288.66389559375, -8035.66551336146,
		1315.7226182880026, -140.81987408191296, 9.477544982980568,
		-0.3637965317362993, 0.006070781973020655
	};
	auto YCombinator = [](auto& RecursiveFunction) {
		auto FixedPoint = [&](auto& Self) {
			return [&, Self](auto&&... Parameters) {
				return RecursiveFunction(Self(Self))(std::forward<decltype(Parameters)>(Parameters)...);
			};
		};
		return FixedPoint(FixedPoint);
	};
	auto EvaluatePolynomial = [&](auto x) {
		auto HornersRule = [&](auto&& Self) {
			return [&, Self](auto CurrentAddress) {
				if (auto CurrentCoefficient = *CurrentAddress; CurrentAddress + 1 == Coefficients.end())
					return CurrentCoefficient;
				else
					return Self(CurrentAddress + 1) * x + CurrentCoefficient;
			};
		};
		return YCombinator(HornersRule)(Coefficients.begin());
	};
	for (auto x : { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 })
		std::cout << static_cast<char>(EvaluatePolynomial(x));
}
