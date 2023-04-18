#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <set>

using namespace std;

struct RecipeS
{
  int nr; // 1
  int ore_bot_ore; // 6
  int clay_bot_ore; // 12
  int obsidian_bot_ore; // 18
  int obsidian_bot_clay; // 21
  int geode_bot_ore; // 27
  int geode_bot_obsidian; // 30
};


set<vector<int>> evaluated;

int evaluate( RecipeS recipe, int day, map<string,int> producers, map<string,int> materials, int & maxscore )
{
  int score = 0;

  vector<int> v = { day, materials["ore"], materials["clay"], materials["obsidian"], materials["geode"], producers["ore"], producers["clay"], producers["obsidian"], producers["geode"] };

  const bool is_in = evaluated.find(v) != evaluated.end();

  if ( is_in )
  {
    return materials["geode"];
  }
  else
  {
    evaluated.insert(v);
  }

  // check repeat
  // cout << day << " " << materials["ore"] << " " << materials["clay"] << " " << materials["obsidian"] << " " << materials["geode"] << " " << producers["ore"] << " " << producers["clay"] << " " << producers["obsidian"] << " " << producers["geode"] << endl;
  
  // Plan production (materials,iterate->plan,materials)
  vector<string> prodplan;
  // check geode bot
  if ( materials["ore"] >= recipe.geode_bot_ore && materials["obsidian"] >= recipe.geode_bot_obsidian )
    prodplan.push_back( "geode" );

  // check obsidian bot
  if ( materials["ore"] >= recipe.obsidian_bot_ore && materials["clay"] >= recipe.obsidian_bot_clay )
    prodplan.push_back( "obsidian" );

  // check clay bot
  if ( materials["ore"] >= recipe.clay_bot_ore )
    prodplan.push_back( "clay" );

  // check ore bot
  if ( materials["ore"] >= recipe.ore_bot_ore )
    prodplan.push_back( "ore" );
  
  prodplan.push_back( "" );

  // Gather resources (producers->materials)
  materials["ore"] += producers["ore"];
  materials["clay"] += producers["clay"];
  materials["obsidian"] += producers["obsidian"];
  materials["geode"] += producers["geode"];

  // Heuristics
  // do not produce on day 24 
  if ( day == 24)
  {
    return materials["geode"];
  }

  if ( day == 23 && (maxscore - materials["geode"]) >=  producers["geode"] +1 )
  {
    return materials["geode"];
  }

  if ( day == 22 && (maxscore - materials["geode"]) >=  2*producers["geode"] +3 )
  {
    return materials["geode"];
  }

  if ( day == 21 && (maxscore - materials["geode"]) >=  3*producers["geode"] +6 )
  {
    return materials["geode"];
  }

  if ( day == 20 && (maxscore - materials["geode"]) >=  4*producers["geode"] +10 )
  {
    return materials["geode"];
  }

  if ( day == 19 && (maxscore - materials["geode"]) >=  5*producers["geode"] +15 )
  {
    return materials["geode"];
  }

  for ( string plan: prodplan )
  {
    // Finish Production (plan->producers)
    if ( !plan.empty() )
      producers[plan] += 1;

    // Next day
    if ( plan == "geode" )
    {
      materials["ore"] -= recipe.geode_bot_ore;
      materials["obsidian"] -= recipe.geode_bot_obsidian;
      score = evaluate( recipe, day+1, producers, materials, maxscore );
      materials["ore"] += recipe.geode_bot_ore;
      materials["obsidian"] += recipe.geode_bot_obsidian;
    }

    if ( plan == "obsidian" )
    {
      materials["ore"] -= recipe.obsidian_bot_ore;
      materials["clay"] -= recipe.obsidian_bot_clay;
      score = evaluate( recipe, day+1, producers, materials, maxscore );
      materials["ore"] += recipe.obsidian_bot_ore;
      materials["clay"] += recipe.obsidian_bot_clay;
    }

    if ( plan == "clay" )
    {
      materials["ore"] -= recipe.clay_bot_ore;
      score = evaluate( recipe, day+1, producers, materials, maxscore );
      materials["ore"] += recipe.clay_bot_ore;
    }

    if ( plan == "ore" )
    {
      materials["ore"] -= recipe.ore_bot_ore;
      score = evaluate( recipe, day+1, producers, materials, maxscore );
      materials["ore"] += recipe.ore_bot_ore;
    }

    if ( plan == "" )
    {
      score = evaluate( recipe, day+1, producers, materials, maxscore );
    }

    if ( !plan.empty() )
      producers[plan] -= 1;

    if ( score > 0 && score > maxscore )
    {
      maxscore = score;
      cout << "day: " << day;
      cout << " ore(" << producers["ore"] << "," << materials["ore"] << ")";
      cout << " clay(" << producers["clay"] << "," << materials["clay"] << ")";
      cout << " obsidian(" << producers["obsidian"] << "," << materials["obsidian"] << ")";
      cout << " geode(" << producers["geode"] << "," << materials["geode"] << ")";
      cout << " score:" << score;
      cout << endl;
    }
  }

  //cout << day << " " << maxscore << " " << score << endl;
  return maxscore;
}

int main() {
  // open the file
  ifstream is("day19.input");
  string str;

  vector<RecipeS> recipes;

  while ( getline( is, str ) )
  {
    istringstream iss(str);
    string sstr;
    int idx=0;
    RecipeS recipe;

    while ( getline( iss, sstr, ' ' ) )
    {
      switch ( idx )
      {
        case 1:
          recipe.nr = stoi(sstr);
          break;
        case 6:
          recipe.ore_bot_ore = stoi(sstr);
          break;
        case 12:
          recipe.clay_bot_ore = stoi(sstr);
          break;
        case 18: 
          recipe.obsidian_bot_ore = stoi(sstr);
          break;
        case 21:
          recipe.obsidian_bot_clay = stoi(sstr);
          break;
        case 27:
          recipe.geode_bot_ore = stoi(sstr);
          break;
        case 30:
          recipe.geode_bot_obsidian = stoi(sstr);
          break;
        default:
          break;
      }
      cout << sstr << '|' << idx << '|';
      idx++;
    }
    cout << endl;
    recipes.push_back(recipe);
  }

  //close the file
  is.close();

  map<string,int> producers;
  map<string,int> materials;
  int score = 0;
  int result = 0;
  producers["ore"] = 1;

  for ( RecipeS recipe : recipes )
  {
    int maxscore = 0;
    evaluated.clear();

    cout << "robot: " << recipe.nr << endl;
    score = evaluate( recipe, 1, producers, materials, maxscore );
    cout << "score: " <<  score << " maxscore: " << maxscore << endl;
    result += ( score * recipe.nr);
    cout << "result: " <<  result << endl;
  }
}
