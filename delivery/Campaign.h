//! @file
//! @brief Header file for the Campaign class
//!
#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

//! Class implementing a game campaign
class Campaign {
  public:
    Campaign();
    Campaign(vector<string> campaignMapOrder);
    vector<string> getCampaignMapOrder();
    void setCampaignMapOrder(vector<string> vs);
    bool isCampaignValid(vector<string> current_maps);
  private:
    vector<string> campaignMapOrder;
};


