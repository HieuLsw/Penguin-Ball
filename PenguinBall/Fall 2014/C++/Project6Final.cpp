//Project 6: Algorithmic Trading
//Created by: Vaishnavi Raman

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>


using namespace std;


class CerealMarkets {
public:
    CerealMarkets(); //Default constructor
    //mutator functions
    //NOTE for methods comment description is included where the method is defined for clarity
    
    void AddBuyOrders(int price);
    void AddSellOrders(int price);
    bool MarketTransactionBuying(int orderPrice, char indexType,int& holdingsB, int& holdingsF, int& holdingsI,int& valuesB, int& valuesF, int& valuesI, int& finalMMCash);
    bool MarketTransactionSelling(int orderPrice, char indexType,int& holdingsB, int& holdingsF, int& holdingsI,int& valuesB, int& valuesF, int& valuesI, int& finalMMCash);
    //Takes no inputs. Deletes the first element in the order buy book... or if there is only one element in the order book it sets it equal to zero
    void DeleteFirstBuy() {
        if (buyOrders.size() > 1) {
            buyOrders.erase(buyOrders.begin()); //deletes the first order
        }
        else {
            buyOrders.at(0) = 0;//if only one element exists we set it back to the default of zero
            firstBuyOrder = 0;
        }
        
    }
        //Takes no inputs. Deletes the first element in the order sell book... or if there is only one element in the order book it sets it equal to zero
    void DeleteFirstSell() {
        if (sellOrders.size() > 1) {
            sellOrders.erase(sellOrders.begin()); //deletes the first order
        }
        else {
            sellOrders.at(0) = 0;
            firstSellOrder = 0;
        }
        
    }
    //Takes no inputs. Returns how many units of an MM property is owned.
    int GetUnitsOwned(){
        return unitsOwned;
    }
    //
    void AddUnitOwned(){
        unitsOwned++;
    }
    void RemoveUnitOwned(){
        unitsOwned--;
    }
    void AddMMBuyOrder(int order){
        MMBuyOrder = order;
    }
    void AddMMSellOrder(int order){
        MMSellOrder = order;
    }
    //accessor functions
    int GetMaxBuy() const{
        return buyOrders.at(0);
    }
    int GetMinSell() const {
        return sellOrders.at(0);
    }
    //accessor functions
    int GetMMBuyOrder() const{
        return MMBuyOrder;
    }
    int GetMMSellOrder() const{
        return MMSellOrder;
    }
protected:
    vector<int> buyOrders;
    vector<int> sellOrders;
private:
    int firstSellOrder;
    int firstBuyOrder;
    int MMBuyOrder;
    int MMSellOrder;
    int unitsOwned;
    int unitValues;
};

class IndexArbitrage: public CerealMarkets {
public:
    IndexArbitrage();
    //mutator functions
    void sellIndex(int sugarBombsMinSell, int flakeyPopsMinSell, int bothCerealsMaxBuy, bool sugarIsMM, bool flakeyIsMM, bool bothCerealsIsMM, int& holdingsB, int& holdingsF, int& holdingsI, int& valuesB, int& valuesF, int& valuesI, int& finalMMCash){
        if (sugarIsMM == true){
            cout << "B: " << sugarBombsMinSell << " (MM sell)" << endl;
            holdingsB--;
            valuesB = sugarBombsMinSell;
            finalMMCash += sugarBombsMinSell;
        }
        else {
            cout << "B: " << sugarBombsMinSell << endl;
            valuesB = sugarBombsMinSell;
        }
        if (flakeyIsMM == true){
            cout << "F: " << flakeyPopsMinSell << " (MM sell)" << endl;
            holdingsF--;
            valuesF = flakeyPopsMinSell;
            finalMMCash += flakeyPopsMinSell;

        }
        else {
            cout << "F: " << flakeyPopsMinSell<< endl;
            valuesF = flakeyPopsMinSell;

        }
        if (bothCerealsIsMM == true) {
            cout << "I: " << bothCerealsMaxBuy << " (MM buy)" << endl;
            holdingsI++;
            valuesI = bothCerealsMaxBuy;
            finalMMCash -= bothCerealsMaxBuy;
        }
        else {
            cout << "I: " << bothCerealsMaxBuy  << endl;
            valuesI = bothCerealsMaxBuy;
        }
        
        
        
        roundProfit = bothCerealsMaxBuy - sugarBombsMinSell - flakeyPopsMinSell;
        totalProfit += roundProfit;
        
        cout << "Index Arbitrage: profit = " << roundProfit << endl;

    }
    void buyIndex(int sugarBombsMaxBuy, int flakeyPopsMaxBuy, int bothCerealsMinSell, bool sugarIsMM, bool flakeyIsMM, bool bothCerealsIsMM, int& holdingsB, int& holdingsF, int& holdingsI, int& valuesB, int& valuesF, int& valuesI, int& finalMMCash){
        if (sugarIsMM == true){
            cout << "B: " << sugarBombsMaxBuy << " (MM buy)" << endl;
            holdingsB++;
            valuesB = sugarBombsMaxBuy;
            finalMMCash -= sugarBombsMaxBuy;

        }
        else {
        cout << "B: " << sugarBombsMaxBuy << endl;
            valuesB = sugarBombsMaxBuy;

        }
        if (flakeyIsMM == true){
        cout << "F: " << flakeyPopsMaxBuy << " (MM buy)" << endl;
            holdingsF++;
            valuesF = flakeyPopsMaxBuy;
            finalMMCash -= flakeyPopsMaxBuy;
        }
        else {
        cout << "F: " << flakeyPopsMaxBuy << endl;
            valuesF = flakeyPopsMaxBuy;
        }
        if (bothCerealsIsMM == true) {
            cout << "I: " << bothCerealsMinSell << " (MM sell)" << endl;
            holdingsI--;
            valuesI = bothCerealsMinSell;
            finalMMCash += bothCerealsMinSell;

        }
        else {
            cout << "I: " << bothCerealsMinSell << endl;
            valuesI = bothCerealsMinSell;

        }
        
        roundProfit = sugarBombsMaxBuy + flakeyPopsMaxBuy - bothCerealsMinSell;
        totalProfit += roundProfit;
        
        cout << "Index Arbitrage: profit = " << roundProfit << endl;

    }
    //accessor function
    int GetFinalProfit() {
        return totalProfit;
    }
private:
    int roundProfit;
    int totalProfit;
    
};

class MarketMaking : public CerealMarkets {
public:
    MarketMaking();
    void AddUnitOwned(){
       holdings++;
    }
    void RemoveUnitOwned(){
       holdings--;
    }
    int GetUnitsOwned(){
        return holdings;
    }
    
private:
    int holdings;
    int values;
    
};


//Default Constructors: initialize all values to zero
CerealMarkets::CerealMarkets() : buyOrders(1), sellOrders(1) {
    buyOrders.at(0) = 0;
    sellOrders.at(0) = 0;
    firstSellOrder = 0;
    firstBuyOrder = 0;
    MMBuyOrder = 0;
    MMSellOrder = 0;
}

IndexArbitrage::IndexArbitrage() {
    roundProfit = 0;
    totalProfit = 0;
}

MarketMaking::MarketMaking(){
    int holdings = 0;
    int values = 0;

}

// If no transaction occurs this function adds the price to the buy order book. Price is taken as an input to add into the vector storing the order requests. Inputs are sorted in descending order.
void CerealMarkets::AddBuyOrders(int price) {
    
    if (firstBuyOrder == 0) { // so first input is not sorted
        buyOrders.at(0) = price;
        firstBuyOrder++;
    }
    else {
        bool isInputed = false;
        for (int i=0; i < buyOrders.size(); i++) {
            while ((price >= buyOrders.at(i)) && (isInputed == false)) {
        buyOrders.insert(buyOrders.begin() + i, price);
        isInputed = true;
            }
        }
        if (isInputed == false){
            buyOrders.push_back(price);
        }
    }
}

// If no transaction occurs this function adds the price to the sell order book. Price is taken as an input to add into the vector storing the order requests.Inputs are sorted in ascending order.
void CerealMarkets::AddSellOrders(int price) {
    
    
    if (firstSellOrder == 0) { // so first input is not sorted
        sellOrders.at(0) = price;
        firstSellOrder++;
    }
    else {
        bool isInputed = false;
        for (int i=0; i < sellOrders.size(); i++) {
            while ((price <= sellOrders.at(i)) && (isInputed == false)) {
                sellOrders.insert(sellOrders.begin() + i, price);
                isInputed = true;
            }
        }
        if (isInputed == false){
            sellOrders.push_back(price);
        }
    }
}

// Takes the buying request price and index type(which market we are operating on) as inputs. Uses the buying request price to see if it is greater than or equal to the smallest selling request(stored at 0 since its in ascending order). If this is true transaction occurs otherwise it doesn't.
bool CerealMarkets::MarketTransactionBuying(int orderPrice, char indexType, int& holdingsB, int& holdingsF, int& holdingsI, int& valuesB, int& valuesF, int& valuesI, int& finalMMCash) {
    
    //checks to ensure that some sell orders to indeed exist
    if (MMSellOrder != 0 && firstSellOrder !=0){
        if (MMSellOrder <= sellOrders.at(0)){
            if (MMSellOrder <= orderPrice) {
            cout << indexType << ": " << MMSellOrder << " (MM sell)" << endl;
                finalMMCash += MMSellOrder;
            MMSellOrder = 0;

                if (indexType == 'I'){
                    holdingsI--;
                    valuesI = MMSellOrder;
                }
                if (indexType == 'F'){
                    holdingsF--;
                    valuesF = MMSellOrder;
                }
                if (indexType == 'B'){
                    holdingsB--;
                    valuesB = MMSellOrder;
                }
            return false;
        }
        }
    }
    if (firstSellOrder != 0) {
        if (sellOrders.at(0) <= orderPrice) {
            cout << indexType << ": " << sellOrders.at(0) << endl;
            if (sellOrders.size() > 1) {
            sellOrders.erase(sellOrders.begin()); //deletes the sell order fullfilled in this scenario from the transaction book
            }
            else {
                sellOrders.at(0) = 0;
                firstSellOrder = 0;
            }
            if (indexType == 'I'){
                valuesI = sellOrders.at(0);
            }
            if (indexType == 'F'){
                valuesF = sellOrders.at(0);
            }
            if (indexType == 'B'){
                valuesB = sellOrders.at(0);
            }
            return false;
        }
    }
    return true;
}
        
 //Takes the selling request price and index type(which market we are operating on) as inputs. Uses the selling request price to see if it is less than or equal to the largest buying request(stored at 0 since its in descending order). If this is true transaction occurs otherwise it doesn't.
            bool CerealMarkets::MarketTransactionSelling(int orderPrice, char indexType, int& holdingsB, int& holdingsF, int& holdingsI, int& valuesB, int& valuesF, int& valuesI, int& finalMMCash) {
    

    //if the MMBid is less it will transact over the prices in the order book
    if (MMBuyOrder != 0 && firstSellOrder != 0){
        //if MM buy order is larger it will transact.
        if (MMBuyOrder >= buyOrders.at(0)){
            if (MMBuyOrder >= orderPrice){
        cout << indexType << ": " << MMBuyOrder << " (MM buy)" << endl;
                finalMMCash -= MMBuyOrder;
                if (indexType == 'I'){
                    holdingsI++;
                    valuesI = MMBuyOrder;

                }
                if (indexType == 'F'){
                    holdingsF++;
                    valuesF = MMBuyOrder;
                }
                if (indexType == 'B'){
                    holdingsB++;
                    valuesB = MMBuyOrder;

                }
                MMBuyOrder = 0;
        return false;
        }
        }
    }
    if (firstBuyOrder != 0){
        if (buyOrders.at(0) >= orderPrice) {
            cout << indexType << ": " << buyOrders.at(0) << endl;
            if (indexType == 'I'){
                valuesI = buyOrders.at(0);
            }
            if (indexType == 'F'){
                valuesF = buyOrders.at(0);
                
            }
            if (indexType == 'B'){
                valuesB = buyOrders.at(0);
            }
            if (buyOrders.size() > 1){
            buyOrders.erase(buyOrders.begin()); //deletes the sell order fullfilled in this scenario from the transaction book
            }
            else {
                buyOrders.at(0) = 0;
                firstBuyOrder = 0;
            }
            return false;
        }
    }
    return true;
}
        


int main() {
  
    CerealMarkets sugarBombs;
    CerealMarkets flakeyPops;
    CerealMarkets bothCereals;
    IndexArbitrage arbitrator;
    MarketMaking sugarBombsMM;
    MarketMaking flakeyPopsMM;
    MarketMaking bothCerealsMM;
    
    
    
    int holdingsB = 0;
    int holdingsF = 0;
    int holdingsI = 0;
    
    int valuesB = 0;
    int valuesF = 0;
    int valuesI = 0;
    
    int finalMMCash = 0;

    string file_name;
    ifstream inFS;
    cin >> file_name;
    
    //inputs the threshold used to determine market making strategies
    int threshold;
    cin >> threshold;
    
    inFS.open(file_name.c_str());
    
    char indexType; //determines if its B, F, I market
    int transactionType; //buying or selling?
    int orderPrice;

    while(inFS >> indexType) {
        inFS >> transactionType;
        inFS >> orderPrice;

         // check to see if a transaction is possible using the MarketTransctionBuying/Selling predicates. Only proceeds to add them  to the viewbook if the transation does NOT go thorugh.
        if (indexType == 'B') {
            if (transactionType == 1) {
                if (sugarBombs.MarketTransactionBuying(orderPrice,indexType,holdingsB, holdingsF, holdingsI, valuesB, valuesF, valuesI, finalMMCash) == true) {
                sugarBombs.AddBuyOrders(orderPrice);
                }
            }
            if (transactionType == -1) {
                if (sugarBombs.MarketTransactionSelling(orderPrice,indexType,holdingsB, holdingsF, holdingsI, valuesB, valuesF, valuesI, finalMMCash) == true) {
                sugarBombs.AddSellOrders(orderPrice);
                }
            }
        }
        if (indexType == 'F') {
            if (transactionType == 1) {
                if (flakeyPops.MarketTransactionBuying(orderPrice,indexType, holdingsB, holdingsF, holdingsI, valuesB, valuesF, valuesI, finalMMCash) == true) {
                flakeyPops.AddBuyOrders(orderPrice);
                }
            }
            if (transactionType == -1) {
                if (flakeyPops.MarketTransactionSelling(orderPrice,indexType,holdingsB, holdingsF, holdingsI, valuesB, valuesF, valuesI, finalMMCash) == true) {
                flakeyPops.AddSellOrders(orderPrice);
                }
            }
        }
        if (indexType == 'I') {
            if (transactionType == 1) {
                if (bothCereals.MarketTransactionBuying(orderPrice,indexType, holdingsB, holdingsF, holdingsI, valuesB, valuesF, valuesI, finalMMCash) == true) {
                    bothCereals.AddBuyOrders(orderPrice);
                }
            }
            if (transactionType == -1) {
                if (bothCereals.MarketTransactionSelling(orderPrice,indexType,holdingsB, holdingsF, holdingsI, valuesB, valuesF, valuesI, finalMMCash) == true) {
                    bothCereals.AddSellOrders(orderPrice);
                }
            }
        }
        
        // Checks condition to see if we can buy index and profit
        
        //first if statement confirms that the bid and ask quotes in the scenarios actually exist
        //second if statement checks to see if transaction would be profitable and whether or not to proceed
        
        bool maxFlakeyBuyIsMM = false;
        bool maxSugarBuyIsMM = false;
        bool minBothSellIsMM = false;
        
        int maxFlakeyBuy;
        int maxSugarBuy;
        int minBothSell;
        
        if (flakeyPops.GetMaxBuy() !=0 && sugarBombs.GetMaxBuy() !=0 && bothCereals.GetMinSell() != 0) {
            
            if (flakeyPops.GetMMBuyOrder() > flakeyPops.GetMaxBuy()) {
                maxFlakeyBuy = flakeyPops.GetMMBuyOrder();
                maxFlakeyBuyIsMM = true;
            }
            else {
                maxFlakeyBuy = flakeyPops.GetMaxBuy();
            }
            
            if (sugarBombs.GetMMBuyOrder() > sugarBombs.GetMaxBuy()) {
                maxSugarBuy = sugarBombs.GetMMBuyOrder();
                maxSugarBuyIsMM = true;
            }
            else {
                maxSugarBuy = sugarBombs.GetMaxBuy();
            }
            
            if ((bothCereals.GetMinSell() > bothCereals.GetMMSellOrder()) && (bothCereals.GetMMSellOrder() != 0)){
                minBothSell = bothCereals.GetMMSellOrder();
                minBothSellIsMM = true;
            }
            else {
                minBothSell = bothCereals.GetMinSell();
            }
            
        if ((maxFlakeyBuy + maxSugarBuy) > minBothSell) {
            arbitrator.buyIndex(maxSugarBuy, maxFlakeyBuy, minBothSell, maxSugarBuyIsMM, maxFlakeyBuyIsMM, minBothSellIsMM, holdingsB, holdingsF, holdingsI, valuesB, valuesF, valuesI, finalMMCash);
            
            //removes the three elements transacted from the order books
            if (maxSugarBuyIsMM == true){
                sugarBombs.AddMMBuyOrder(0);
            }
            else {
                sugarBombs.DeleteFirstBuy();
            }
            if (maxFlakeyBuyIsMM == true){
                flakeyPops.AddMMBuyOrder(0);
            }
            else {
                flakeyPops.DeleteFirstBuy();
            }
            if (minBothSellIsMM == true) {
                bothCereals.AddMMSellOrder(0);
            }
            else {
                bothCereals.DeleteFirstSell();
            }
            
        }
        }
        
        
        bool minFlakeySellIsMM = false;
        bool minSugarSellIsMM = false;
        bool maxBothBuyIsMM = false;
        
        int minFlakeySell;
        int minSugarSell;
        int maxBothBuy;
        //first if statement confirms that the bid and ask quotes in the scenarios actually exist
        //second if statement checks to see if transaction would be profitable and whether or not to proceed
        if (flakeyPops.GetMinSell() !=0 && sugarBombs.GetMinSell() != 0 && bothCereals.GetMaxBuy() != 0){

            if ((flakeyPops.GetMMSellOrder() < flakeyPops.GetMinSell()) && (flakeyPops.GetMMSellOrder() != 0)) {
                minFlakeySell = flakeyPops.GetMMSellOrder();
                minFlakeySellIsMM = true;
            }
            else {
                minFlakeySell = flakeyPops.GetMinSell();
            }
            
            if ((sugarBombs.GetMMSellOrder() < sugarBombs.GetMinSell()) && (sugarBombs.GetMMSellOrder() != 0)) {
                minSugarSell = sugarBombs.GetMMSellOrder();
                minSugarSellIsMM = true;
            }
            else {
                minSugarSell = sugarBombs.GetMinSell();
            }
            
            if (bothCereals.GetMaxBuy() < bothCereals.GetMMBuyOrder() ){
                maxBothBuy = bothCereals.GetMMBuyOrder();
                maxBothBuyIsMM = true;
            }
            else {
                maxBothBuy = bothCereals.GetMaxBuy();
            }
            

        // Checks condition to see if we can sell index and profit
        if (maxBothBuy > (minFlakeySell + minSugarSell)) {
            arbitrator.sellIndex(minSugarSell, minFlakeySell, maxBothBuy, minSugarSellIsMM, minFlakeySellIsMM, maxBothBuyIsMM, holdingsB, holdingsF, holdingsI,valuesB, valuesF, valuesI, finalMMCash);
            
            
            if (minSugarSellIsMM == true){
                sugarBombs.AddMMSellOrder(0);
            }
            else {
                sugarBombs.DeleteFirstSell();
            }
            if (minFlakeySellIsMM == true){
                flakeyPops.AddMMSellOrder(0);
            }
            else {
                flakeyPops.DeleteFirstSell();
            }
            if (maxBothBuyIsMM == true) {
                bothCereals.AddMMBuyOrder(0);
            }
            else {
                bothCereals.DeleteFirstBuy();
            }
            
        }
        }
        
        
        //NOW we do the market making strategy
        //checks that all foteh bids exist
        if (flakeyPops.GetMinSell() != 0 && flakeyPops.GetMaxBuy() != 0){
            //checks to see if threshold is met
            if ((flakeyPops.GetMinSell() - flakeyPops.GetMaxBuy()) >= threshold){
                //if buy order is below bid place a new order 1 above the bid
                if (flakeyPops.GetMaxBuy() == flakeyPops.GetMMBuyOrder()){
                    //here no action is taken
                }
                else if (flakeyPops.GetMaxBuy() > flakeyPops.GetMMBuyOrder()){
                    flakeyPops.AddMMBuyOrder((flakeyPops.GetMaxBuy())+1);
                }
                if (flakeyPops.GetMinSell() == flakeyPops.GetMMSellOrder()){
                    //here no action is taken
                }
                else if ((flakeyPops.GetMinSell() < flakeyPops.GetMMSellOrder()) or flakeyPops.GetMMSellOrder() == 0){
                    flakeyPops.AddMMSellOrder((flakeyPops.GetMinSell())-1);
                }
            }
        }

        if (sugarBombs.GetMinSell() != 0 && sugarBombs.GetMaxBuy() != 0){
            //checks to see if threshold is met
            if ((sugarBombs.GetMinSell() - sugarBombs.GetMaxBuy()) >= threshold){
                //if buy order is below bid place a new order 1 above the bid
                if (sugarBombs.GetMaxBuy() > sugarBombs.GetMMBuyOrder()){
                    sugarBombs.AddMMBuyOrder((sugarBombs.GetMaxBuy())+1);
                }
                if (sugarBombs.GetMinSell() < sugarBombs.GetMMSellOrder() or sugarBombs.GetMMSellOrder() == 0){
                    sugarBombs.AddMMSellOrder((sugarBombs.GetMinSell())-1);
                }
            }
        }

        if (bothCereals.GetMinSell() != 0 && bothCereals.GetMaxBuy() != 0){
            //checks to see if threshold is met
            if ((bothCereals.GetMinSell() - bothCereals.GetMaxBuy()) >= threshold){
                //if buy order is below bid place a new order 1 above the bid
                if (bothCereals.GetMaxBuy() > bothCereals.GetMMBuyOrder()){
                    bothCereals.AddMMBuyOrder((bothCereals.GetMaxBuy())+1);
                }
                if (bothCereals.GetMinSell() < bothCereals.GetMMSellOrder() or bothCereals.GetMMSellOrder() == 0){
                    bothCereals.AddMMSellOrder((bothCereals.GetMinSell())-1);
                }
            }
        }
    }
    inFS.close();
    
    cout << "IA final holdings: cash = " << arbitrator.GetFinalProfit() << endl;
    cout << "MM final holdings: cash = " << finalMMCash << endl;
    cout << "Security B: " << holdingsB << " units, value = " << holdingsB * valuesB << endl;
    cout << "Security F: " << holdingsF << " units, value = " << holdingsF * valuesF << endl;
    cout << "Security I: " << holdingsI << " units, value = " << holdingsI * valuesI << endl;
    cout << "Total profit is " << finalMMCash + (holdingsB * valuesB) + (holdingsF * valuesF) + (holdingsI * valuesI)  << "." << endl;
    
    
    return 0;
}