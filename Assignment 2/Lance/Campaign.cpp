//! @file
//! @brief Implementation file for the Campaign class
//!

#include "Campaign.h"

Campaign::Campaign() {
  campaignMapOrder = {};
}

Campaign::Campaign(vector<string> cmo) {
  campaignMapOrder = cmo;
}

vector<string> Campaign::getCampaignMapOrder() {
  return campaignMapOrder;
}

void Campaign::setCampaignMapOrder(vector<string> vs) {
  campaignMapOrder = vs;
}
