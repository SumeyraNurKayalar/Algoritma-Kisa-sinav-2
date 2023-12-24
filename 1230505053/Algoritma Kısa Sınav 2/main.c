#include <stdio.h>
#include <stdlib.h>

/*Kodun �al��mas� i�in ilk olarak a��k artt�rmaya kat�lacak ki�i say�s� girilir ve teker teker bu ki�ilerin
�deyece�i miktarlar girilir.Bu �deme miktarlar� ve ki�ilerin isimleri girildikten sonra program en sonunda �rnek olarak
girilmi� item cismini en �ok �deme yapan ki�iye satar ve bu �deme miktar�n� verir. Ayriyeten bunun
alt�nda a��k artt�rmaya kat�lm�� t�m kat�l�mc�lar�n ad� ve �deme bedelleri yazar.*/

// Typedef for Bid struct
typedef struct {
    char bidderName[100];
    double amount;
} Bid;

// Typedef for AuctionItem struct
typedef struct {
    char itemName[50];
    Bid *bids;
    int numBids;
    double currentBid;
} AuctionItem;

// Functions to initialize an auction item
void initializeAuctionItem(AuctionItem *item, const char *itemName) {
    snprintf(item->itemName, sizeof(item->itemName), "%s", itemName);
    item->bids = NULL;
    item->numBids = 0;
    item->currentBid = 0.0;
}

// Functions to place a bid on an auction item
void placeBid(AuctionItem *item, const char *bidderName, double bidAmount) {
    if (bidAmount > item->currentBid) {
        item->currentBid = bidAmount;
    }

    item->bids = realloc(item->bids, (item->numBids + 1) * sizeof(Bid));

    snprintf(item->bids[item->numBids].bidderName, sizeof(item->bids[item->numBids].bidderName), "%49s", bidderName);
    item->bids[item->numBids].amount = bidAmount;

    item->numBids++;

    printf("Bid placed successfully by %s for %.2f\n", bidderName, bidAmount);
}

// Function to get the number of bidders from the user
int getNumBidders() {
    int numBidders;
    printf("Enter the number of bidders: ");
    scanf("%d", &numBidders);
    return numBidders;
}

// Function to get bidder information from the user
void getBidderInfo(AuctionItem *item) {
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

// Function to display all bidders
void displayAllBidders(const AuctionItem *item) {
    printf("All Bidders for item: %s\n", item->itemName);
    printf("Bidders:\n");
    for (int i = 0; i < item->numBids; i++) {
        printf("%s - %.2f\n", item->bids[i].bidderName, item->bids[i].amount);
    }
}

// Function to display the auction results, including the highest bidder
void displayAuctionResults(const AuctionItem *item) {
    printf("Auction results for item: %s\n", item->itemName);
    printf("Current highest bid: %.2f\n", item->currentBid);

    if (item->numBids > 0) {
        printf("Highest Bidder: %s - %.2f\n", item->bids[item->numBids - 1].bidderName, item->bids[item->numBids - 1].amount);
    } else {
        printf("No bids placed yet.\n");
    }

    displayAllBidders(item);
}

// Function to free memory allocated for bids
void cleanupAuctionItem(AuctionItem *item) {
    free(item->bids);
}

int main() {
    AuctionItem myItem;
    initializeAuctionItem(&myItem, "Item");

    getBidderInfo(&myItem);

    displayAuctionResults(&myItem);

    cleanupAuctionItem(&myItem);

    return 0;
}
