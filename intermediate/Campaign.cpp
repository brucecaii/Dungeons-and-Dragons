//! @file
//! @brief Implementation file for the Campaign class
//!

#include "Campaign.h"

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
