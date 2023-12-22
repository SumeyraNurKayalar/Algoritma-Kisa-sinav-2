#include <stdio.h>
#include <stdlib.h>

/*Kodun çalışması için ilk olarak açık arttırmaya katılacak kişi sayısı girilir ve teker teker bu kişilerin 
ödeyeceği miktarlar girilir.Bu ödeme miktarları ve kişilerin isimleri girildikten sonra program en sonunda örnek olarak 
girilmiş item cismini en çok ödeme yapan kişiye satar ve yapılan ödeme miktarını verir. Ayriyeten bunun
altında açık arttırmaya katılmış tüm katılımcıların adı ve ödeme bedelleri yazar.*/

// Creates a struct to represent a bid
struct Bid {
    char bidderName[100];
    double amount;
};

// Creates a struct to represent an auction item
struct AuctionItem {
    char itemName[50];
    struct Bid *bids;  // creates an array to store the bids
    int numBids;       // creates a number of the bids
    double currentBid; // Currents the highest bid
};

// Functions to initialize an auction item
void initializeAuctionItem(struct AuctionItem *item, const char *itemName) {
    snprintf(item->itemName, sizeof(item->itemName), "%s", itemName);
    item->bids = NULL;
    item->numBids = 0;
    item->currentBid = 0.0;
}

// Functions to place a bid on an auction item
void placeBid(struct AuctionItem *item, const char *bidderName, double bidAmount) {
    // Checks if the bid is higher than the current highest bid
    if (bidAmount > item->currentBid) {
        // Updates the current highest bid
        item->currentBid = bidAmount;
    }

    // Allocates memory for a new bid
    item->bids = realloc(item->bids, (item->numBids + 1) * sizeof(struct Bid));

    // Stores the bid information
    snprintf(item->bids[item->numBids].bidderName, sizeof(item->bids[item->numBids].bidderName), "%49s", bidderName);
    item->bids[item->numBids].amount = bidAmount;

    // Increments the number of bids
    item->numBids++;

    printf("Bid placed successfully by %s for %.2f\n", bidderName, bidAmount);
}

// Functions to get the number of bidders from the user
int getNumBidders() {
    int numBidders;
    printf("Enter the number of bidders: ");
    scanf("%d", &numBidders);
    return numBidders;
}

// Functions to get bidder information from the user
void getBidderInfo(struct AuctionItem *item) {
    int numBidders = getNumBidders();
    for (int i = 0; i < numBidders; i++) {
        char bidderName[50];
        double bidAmount;

        printf("Enter bidder name: ");
        scanf("%s", bidderName);

        printf("Enter bid amount: ");
        scanf("%lf", &bidAmount);

        placeBid(item, bidderName, bidAmount);
    }
}

// Functions to display all bidders
void displayAllBidders(const struct AuctionItem *item) {
    printf("All Bidders for item: %s\n", item->itemName);
    printf("Bidders:\n");
    for (int i = 0; i < item->numBids; i++) {
        printf("%s - %.2f\n", item->bids[i].bidderName, item->bids[i].amount);
    }
}

// Functions to display the auction results
void displayAuctionResults(const struct AuctionItem *item) {
    printf("Auction results for item: %s\n", item->itemName);
    printf("Current highest bid: %.2f\n", item->currentBid);

    displayAllBidders(item);
}

// Functions to free memory allocated for bids
void cleanupAuctionItem(struct AuctionItem *item) {
    free(item->bids);
}

int main() {
    // Creates an auction item
    struct AuctionItem myItem;
    initializeAuctionItem(&myItem, "Item");

    // Gets bidder information from the user
    getBidderInfo(&myItem);

    // Displays auction results
    displayAuctionResults(&myItem);

    // Cleans up memory
    cleanupAuctionItem(&myItem);

    return 0;
}
