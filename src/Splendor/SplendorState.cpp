#include "SplendorState.h"
#include <algorithm>
#include <random>
#include <numeric>
SplendorState::SplendorState(int playerCount) : State(playerCount){
    if(gameSeed > 0){
        std::default_random_engine generator(gameSeed);
    }
    auto rng = std::default_random_engine {};
    vector <devCard> commonDevsCopy = commonDevs;
    std::shuffle(std::begin(commonDevsCopy), std::end(commonDevsCopy), rng);
    vector <devCard> rareDevsCopy = rareDevs;
    std::shuffle(std::begin(rareDevsCopy), std::end(rareDevsCopy), rng);
    vector <devCard> epicDevsCopy = epicDevs;
    std::shuffle(std::begin(epicDevsCopy), std::end(epicDevsCopy), rng);
    deckCards = {commonDevsCopy,rareDevsCopy,epicDevsCopy};
    for(int i = 0; i < deckCards.size();i++){
        shopCards.push_back(vector<devCard>());
    }
    for(int i = 0; i < 4; i++){

        for(int j = 0; j < deckCards.size(); j++){
            shopCards[j].push_back(deckCards[j][deckCards[j].size() - 1 - i]);
            
        }
        for(int j = 0; j < deckCards.size(); j++){
            deckCards[j].pop_back();
        }
    }
    
    vector <vector<int>> nobleCopy = nobles;
    std::shuffle(std::begin(nobleCopy), std::end(nobleCopy), rng);
    unclaimedNobles = std::vector(nobleCopy.begin(), nobleCopy.begin() + playerCount + 1);

    playerAssets = vector<vector<devCard>>();
    playerBalance = vector<vector<int>>();
    playerDiscounts = vector<vector<int>>();
    playerAssets = vector<vector<devCard>>();
    playerNobles = vector<vector<noble>>();
    
    for(int i = 0; i < playerCount; i++){
        playerAssets.push_back(vector<devCard>());
        playerBalance.push_back({0,0,0,0,0,0});
        playerDiscounts.push_back({0,0,0,0,0,0});
        playerReserves.push_back(vector<devCard>());
        playerNobles.push_back(vector<noble>());
    }
    shopGems = {7,7,7,7,7,5};
    playerPoints = vector<int>();
    for(int i = 0; i < playerCount; i++){
        playerPoints.push_back(0);
    }
}
SplendorState::SplendorState(const SplendorState& other) : State(other.playerCount){
    
    SplendorState *ret = new SplendorState(playerCount);
    ret-> shopCards = vcopy(shopCards); // IMPLEMENT devcard copy compatability with vcopy
    // replace copy functions with copy constructors.
    ret->unclaimedNobles = vcopy(unclaimedNobles);
    ret->playerAssets = vcopy(playerAssets);
    ret->playerReserves = vcopy(playerReserves);
    ret->playerNobles = vcopy(playerNobles);
    ret->playerBalance = vcopy(playerBalance);
    ret->playerDiscounts = vcopy(playerDiscounts);
    ret->shopGems = vcopy(shopGems);
    ret->playerPoints = vcopy(playerPoints);
    ret->deckCards = vcopy(deckCards);
    return ret;
}
bool SplendorState::has_won(int playerNum){
    return playerPoints[playerNum] >= pointsToWin;
}
bool SplendorState::is_valid_move(std::string move){
    cout << "checking if move is valid" << endl;
    auto movecp = move;
    vector<string> splits = vector<string>();
    splits = split(move," ");
    std::string move_type = splits[0];

    cout << "move type is:" << move_type << endl;
    if(move_type == "b" || move_type == "br"){
        devCard *target_cardp = nullptr;
        vector<int> gemlist = vector<int>();
        if(move_type == "b"){
            vector<int> buy_row_col = splitint(splits[1],",");
            int buy_row = buy_row_col[0];
            int buy_col = buy_row_col[1];
            if(!(buy_row < shopCards.size() && buy_col < shopCards[buy_row].size())){
                // bad target card.
                cout << "Target card to buy does not exist" << endl;
                return false;
            }
            target_cardp = &(shopCards[buy_row][buy_col]);

        }
        if(move_type == "br"){
            int reserve_index = atoi(splits[1].c_str());
            target_cardp =  &(playerReserves[currentTurn][reserve_index]);
        }
        
        gemlist = splitint(splits[2],",");
        devCard target_card = *target_cardp;
        int gold_sum = 0;
        for(int i = 0; i < playerBalance[currentTurn].size(); i++){
            int goldUseCount = gemlist[i];
            if(target_card.get_cost((devColour)i) > playerBalance[currentTurn][i] + goldUseCount + playerDiscounts[currentTurn][i]){
                // Too expensive.
                cout << "Targeted card to buy is too expensive! for colour: "<< (devColour)i << endl;
                return false;
            }
            gold_sum += goldUseCount;
        }
        if(playerBalance[currentTurn][GOLD] < gold_sum){
            cout << "not enough gold to cover used gold!";
            return false;
        }
    }
    if(move_type == "r"){
        vector<int> buy_row_col = splitint(splits[1],",");
        int buy_row = buy_row_col[0];
        int buy_col = buy_row_col[1];
        vector<int> discardlist = splitint(splits[2],",");
        int discard_sum = 0;
        int PlayerBalanceSum = std::accumulate(playerBalance[currentTurn].begin(),playerBalance[currentTurn].end(),0);
        
        for(int i = 0; i < discardlist.size(); i++){
            
            discard_sum += discardlist[i];
            int take = 0;
            if(i == GOLD && (shopGems[GOLD] > 0)){
                take = 1;
            }
            if(playerBalance[currentTurn][i] + take < discardlist[i]){
                cout << "Bad move: trying to discard gems the player doesn't have!" << endl;
                return false;
            }
            
        }
        if (PlayerBalanceSum + (shopGems[GOLD] > 0) - discard_sum > 10){
            cout << "Bad move: Can't keep more than 10 gems" << endl;
            return false;
        }
        if (buy_row < 0){
            cout << "buy_row too small" << endl;
            return false;
        }
        if (buy_row >= shopCards.size()){
            cout << "buy_row too big" << endl;
            return false;
        }
        if(buy_col >= shopCards[buy_row].size()){
            cout << "buy_col too big" << endl;
            return false;
        }
        if(buy_col <= -2){
            cout << "buy_col too small" << endl;
            return false;
        }
        return true;
    }
    if(move_type == "t"){
        vector<int> gemlist = splitint(splits[1],",");
        cout << "first split done!" << endl;
        vector<int> discardlist = splitint(splits[2],",");
        int sum = 0;
        int playerSum = 0;
        int discardSum = 0;
        int max = 0;
        for(int i = 0; i < playerBalance[currentTurn].size(); i++){
            cout << i << endl;
            int take = gemlist[i];
            int discard = discardlist[i];
            if( shopGems[i]<take){
                // Too expensive.
                cout << "bad move: cant take more gems than exist in shop for colour:" << (devColour)i  << endl;
                return false;
            }
            if(take > 1 && shopGems[i] < 5){
                // cant take 2 if only 5 left.
                cout << "bad move: can't take 2 gems when <= 5 left. for colour:" << (devColour)i  << endl;
                return false;
            }
            sum += take;
            if(take > max){
                max = take;
            }
            if(i == GOLD && take > 0){
                cout << "bad move: can't take gold directly" << endl;
                return false;
            }
            playerSum += playerBalance[currentTurn][i];
            discardSum += discard;

            if(playerBalance[currentTurn][i] + take < discard){

                cout << "bad move: can't discard more gems than is owned. for colour:" << (devColour)i << endl;
                return false;
            }
            
        }
        if(playerSum + sum - discardSum > 10){
            cout << "bad move: can't end with more than 10 gems" << endl;
            return false;
        }
        if(!((sum == 2 && max == 2) || (sum == 3 && max == 1))){
            cout << "bad move: taking the incorrect amount of gems. Max: " << max << " Sum: " << sum  << endl;

            return false;
        }
        return (sum == 2 && max == 2) || (sum == 3 && max == 1); 
    }
    int targetNobleIndex = atoi(splits[splits.size()-1].c_str());
    if(targetNobleIndex >= 0){
        if(targetNobleIndex >= unclaimedNobles.size()){
            cout << "bad move: incorrect noble targetting" << endl;
            return false;
        }
        noble targetNoble = unclaimedNobles[targetNobleIndex];
        bool canClaim = true;
        for(int j = 0; j < targetNoble.size(); j++){
            if(targetNoble[j] > playerDiscounts[currentTurn][j]){
                canClaim = false;
                break;
            }
        }
        if(!canClaim){
            cout << "bad move: can't claim this noble!" << endl;
            return false;
        }
    }
    return true;
}

// TODO:
// DEBUG IsValid/Apply move
bool SplendorState::apply_move(std::string move){
    if(!is_valid_move(move)){
        cout << "Invalid move!!" << endl;
        return false;
    }
    cout << "Valid move!" << endl;
    // Move format is one of:
    // b <shop card coords> <list of gems to use gold instead of> <noble choice>? (buy shop card at coord)
    // r <shop card coords> <list of gems to discard> <noble choice>? (reserve shop card at coord) 
    // br <reserve card coords> <list of gems to use gold instead of> <noble choice>?
    // t <list of gems to take from stockpile> <list of gems to discard> <noble choice>?
    // we assume all players know the rules.
    // a <list of things> looks like a,b,c,d,e,a .. etc
    // example:
    // b 1,3 2,0,0,1,0 1
    // the above would use 3 gold as replacement for some gems, and buys the rare developement card on the rightmost side.
    // and if there is a noble to chosen, it chooses the noble at position 1.
    // when nobles or shop cards get taken, and cant be replaced, all items get shifted down to fill the hole.

    auto movecp = move;
    vector<string> splits = split(movecp, " ");
    std::string move_type = splits[0];

    if(move_type == "b" || move_type == "br"){
        devCard *target_cardp = nullptr;
        // take card from shop
        if(move_type == "b"){
            vector<int> buy_row_col = splitint(splits[1],",");
            int buy_row = buy_row_col[0];
            int buy_col = buy_row_col[1];
            target_cardp = &(shopCards[buy_row][buy_col]);

            shopCards[buy_row].erase(shopCards[buy_row].begin() + buy_col);
            if(deckCards[buy_col].size() > 0){
                devCard deckCard = deckCards[buy_col][deckCards[buy_col].size() - 1];
                shopCards[buy_col].push_back(deckCard);
                deckCards[buy_col].pop_back();
            }
        }
        // take card from reserves
        if(move_type == "br"){
            int reserve_index = atoi(splits[1].c_str());
            target_cardp =  &(playerReserves[currentTurn][reserve_index]);
            playerReserves[currentTurn].erase(playerReserves[currentTurn].begin() + reserve_index);
        }
        devCard target_card = *target_cardp;
        vector<int> gemlist = splitint(splits[2],",");
        // lose gems from bought card
        int gold_sum = 0;
        for(int i = 0; i < playerBalance[currentTurn].size(); i++){
            int goldUseCount = gemlist[i];
            playerBalance[currentTurn][i] -= target_card.get_cost((devColour)i) - goldUseCount - playerDiscounts[currentTurn][i];
            gold_sum += goldUseCount;
        }
        // lose gold from buying card, and get card.
        playerBalance[currentTurn][GOLD] -= gold_sum;
        playerAssets[currentTurn].push_back(target_card);
        playerDiscounts[currentTurn][target_card.colour] += 1;
        
    }
    if(move_type == "r"){
        // take card from shop
        vector<int> buy_row_col = splitint(splits[1],",");
        int buy_row = buy_row_col[0];
        int buy_col = buy_row_col[1];
        devCard target_card = shopCards[buy_row][buy_col];
        playerReserves[currentTurn].push_back(target_card);
        shopCards[buy_row].erase(shopCards[buy_row].begin() + buy_col);
        // get 1 gold, if available.
        vector<int> discards = splitint(splits[2],",");
        if(shopGems[GOLD] > 0){
            playerBalance[currentTurn][GOLD] += 1;
            shopGems[GOLD] -= 1;
        }
        // discard gems
        for(int i = 0; i < discards.size();i++){
            playerBalance[currentTurn][i] -= discards[i];
        }

    }
    if(move_type == "t"){
        // take and discard gems
        vector<int> gemlist = splitint(splits[1],",");
        vector<int> discardlist = splitint(splits[2],",");
        for(int i = 0; i < playerBalance[currentTurn].size(); i++){
            int take = gemlist[i]; 
            int discard = discardlist[i];
            
            shopGems[i] -= take - discard;
            playerBalance[currentTurn][i] += take - discard;
        }
    }
    // check nobles
    for(int i = 0; i < unclaimedNobles.size();i++){
        noble uNoble = unclaimedNobles[i];
        bool canClaim = true;
        for(int j = 0; j < uNoble.size(); j++){
            if(uNoble[j] > playerDiscounts[currentTurn][j]){
                canClaim = false;
                break;
            }
        }
        if(canClaim){
            if(i == atoi(splits[splits.size()-1].c_str())){
                // CLAIM NOBLE
                playerPoints[currentTurn] += noble_value;
                playerNobles[currentTurn].push_back(unclaimedNobles[i]);
                unclaimedNobles.erase(unclaimedNobles.begin() + i);
                break;
            }
        }
    }
    currentTurn = (currentTurn + 1) % playerCount;
    return true;
}
// TODO: display (done), get_board, and clone.

std::string SplendorState::display(){
    string ret = "";
    ret += "It is player " + std::to_string(currentTurn) + " turn\n";
    ret.append("Player assets: --------------- \n");
    for(int i = 0; i < playerCount; i++){
        ret += "Player " + std::to_string(i) + ":\n";
        ret = ret + "Points: " + std::to_string(playerPoints[i]) + "\n";
        ret += "Assets:\n";
        for(int j = 0; j < playerAssets[i].size();j++){
            devCard asset = playerAssets[i][j];
            ret += " " + std::to_string(asset.colour) + "," + std::to_string(asset.points);
        }
        ret += "Reserved cards: \n";
        for(int j = 0; j < playerReserves[i].size();j++){
            devCard reserve = playerReserves[i][j];
            for(int col = 0; col < colourCount; col++){
                if(col > 0){
                    ret += ",";
                }
                ret += std::to_string(reserve.get_cost((devColour)(col)));
            }
            ret +=  " " + std::to_string(reserve.colour) + "," + std::to_string(reserve.points);
            ret += "\n";
            
        }
        ret += "Balance: \n";
        for(int col = 0; col < playerBalance[i].size(); col++){
            if(col > 0){
                ret += ",";
            }
            ret += std::to_string(playerBalance[i][col]);
        }
        ret += "\n";
        ret += "Noble count: " + std::to_string(playerNobles[i].size()) + "\n";
        ret += "\n";
    }
    
    
    ret.append("Current Shop: --------------- \n");
    ret += "shop gems: ";
    for(int i = 0; i < shopGems.size(); i++){
        ret += std::to_string(shopGems[i]) + ",";
    }
    ret += "\n";
    for(int i = 0; i < shopCards.size();i++){
        ret +=  "shop " + std::to_string(i) + ":\n";
        
        for(int j = 0; j < shopCards[i].size();j++){
            ret += "(";
            ret += "cost:(";
            devCard shopCard = shopCards[i][j];
            for(int col = 0; col < colourCount; col++){
                if(col > 0){
                    ret += ",";
                }
                ret += std::to_string(shopCard.get_cost((devColour)(col)));
            }
            ret += "), colour: ";
            ret += to_string(shopCard.colour);
            ret += ", points: " + to_string(shopCard.points) + ") | ";
        }
        ret += "\n";
    }
    
    ret.append("Remaining Nobles: --------------- \n");
    for(int i = 0; i < unclaimedNobles.size();i++){
        noble nob = unclaimedNobles[i];
        ret.append("Noble "+ to_string(i) +" requirements: ");
        ret += "(";
        for(int j = 0; j < nob.size();j++){
            if(j > 0){
                ret += ",";
            }
            ret += std::to_string(nob[j]);
        }
        ret += ")\n";
    }

    return ret;
}

// needs debugging
SplendorState *SplendorState::clone(){
    
    SplendorState *ret = new SplendorState(playerCount);
    ret-> shopCards = vcopy(shopCards); // IMPLEMENT devcard copy compatability with vcopy
    // replace copy functions with copy constructors.
    ret->unclaimedNobles = vcopy(unclaimedNobles);
    ret->playerAssets = vcopy(playerAssets);
    ret->playerReserves = vcopy(playerReserves);
    ret->playerNobles = vcopy(playerNobles);
    ret->playerBalance = vcopy(playerBalance);
    ret->playerDiscounts = vcopy(playerDiscounts);
    ret->shopGems = vcopy(shopGems);
    ret->playerPoints = vcopy(playerPoints);
    ret->deckCards = vcopy(deckCards);
    return ret;
}
void* SplendorState::get_board(){
    return NULL;
}
/*
class SplendorState : public State{
    public:
        SplendorState(int playerCount);
        vector<vector<devCard>> shopCards;
        vector<noble> unclaimedNobles;
        vector<vector<devCard>> playerAssets;
        vector<vector<devCard>> playerReserves;
        vector<vector<noble>> playerNobles;
        vector<vector<int>> playerBalance;
        vector<vector<int>> playerDiscounts;
        vector<int> shopGems;
        vector<int> playerPoints;
        vector<vector<devCard>> deckCards;
        virtual bool has_won(int playerNum);
        int game_result();
        bool apply_move(std::string move);
        void* get_board();
        std::string display();
        void print();
        SplendorState* clone();
    protected:
        virtual bool is_valid_move(std::string move);
};
*/
