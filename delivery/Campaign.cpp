//! @file
//! @brief Implementation file for the Campaign class
//!
#include <iostream>
#include "Campaign.h"

using std::cout;
using std::endl;

Campaign::Campaign() {
  this->campaignMapOrder = {};
}

Campaign::Campaign(vector<string> cmo) {
  this->campaignMapOrder = cmo;
}

vector<string> Campaign::getCampaignMapOrder() {
  return this->campaignMapOrder;
}

void Campaign::setCampaignMapOrder(vector<string> vs) {
  this->campaignMapOrder = vs;
}

bool Campaign::isCampaignValid(vector<string> current_maps) {
  // Check campaign is non-empty
  this->campaignMapOrder.shrink_to_fit();
  if (this->campaignMapOrder.size() < 1) {
    cout << "INVALID: Campaign is empty." << endl;
    return false;
  }

  // Check all maps in campaign exist
  for (int i = 0; i < (int)this->campaignMapOrder.size(); i++) {
    bool campaignMapExists = false;
    for (int j = 0; j < (int)current_maps.size(); j++) {
      if (this->campaignMapOrder[i] == current_maps[j]) {
        campaignMapExists = true;
      }
    }
    if (!campaignMapExists) {
    cout << "INVALID: A map within campaign doesn't exist." << endl;
      return false;
    }
  }
  return true;
}
