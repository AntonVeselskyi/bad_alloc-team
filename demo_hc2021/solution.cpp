#include <iostream>
#include <utility>
#include "getline.h"
#include "output.h"
#include "entities.h"
#include "decider.h"

int main(int argc, char *argv[]) {
    FileParser parser(argv[1]);

    FileOutput output(string(argv[1]) + "_res");

    Pizzas pizzas;
    int pizzaCount, twoPersonTeamCount, threePersonTeamCount, fourPersonTeamCount;

    parser.get_next_line(pizzaCount, twoPersonTeamCount, threePersonTeamCount, fourPersonTeamCount);

    for (int i = 0; i < pizzaCount; ++i) {
        int numberOfIngredients;
        std::string ingredientsStr;
        parser.get_next_line(numberOfIngredients);

        std::set<string> ingredients;
        for (int j = 0; j < numberOfIngredients; j++) {
            std::string ingredient;
            parser.get_next_line(ingredient);
            ingredients.insert(ingredient);
        }
        if (pizzas.find(ingredients) != pizzas.end()) {
            pizzas[ingredients].push_back(i);
        } else {
            std::vector<int> temp;
            temp.push_back(i);
            pizzas.insert({ingredients, temp});
        }
    }



//    Plz don't remove me
//    for (auto &pizza : pizzas) {
//        for (const auto & it : pizza.first)
//            cout << ' ' << it;
//        for(const auto  & it : pizza.second){
//            cout << ' ' << it;
//        }
//        cout << '\n';
//    }
    //Usage example
    //output.write_pizza_result(PizzaIndexes vector)
}