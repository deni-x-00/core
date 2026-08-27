using namespace QPI;
constexpr uint64 QUOTTERY_INITIAL_MAX_EVENT = 4096;
constexpr uint64 QUOTTERY_MAX_CONCURRENT_EVENT = QUOTTERY_INITIAL_MAX_EVENT * X_MULTIPLIER; // Maximum number of concurrent events (at the same time)
constexpr uint64 QUOTTERY_MAX_NUMBER_OF_USER = QUOTTERY_MAX_CONCURRENT_EVENT * 2048;

constexpr uint64 QUOTTERY_PERCENT_DENOMINATOR = 1000; // 1000 == 100%
constexpr uint64 QUOTTERY_HARD_CAP_CREATOR_FEE = 50; // 5%

constexpr uint64 QUOTTERY_DOUBLE_BUFFER_SIZE = QUOTTERY_MAX_CONCURRENT_EVENT * 2; // bug in SC verify tool, need this to bypass

constexpr uint64 QUOTTERY_CONTRACT_ASSET_NAME = 1498567761ULL;

constexpr uint32 QUOTTERY_DISPUTE_WINDOW = 1000;
constexpr uint64 QUOTTERY_INVALID_DATETIME = 1;
constexpr uint64 QUOTTERY_INSUFFICIENT_FUND = 5;
constexpr uint64 QUOTTERY_INVALID_EVENT_ID = 6;
constexpr uint64 QUOTTERY_INVALID_POSITION = 7;
constexpr uint64 QUOTTERY_OUT_OF_MEMORY = 8;
constexpr uint64 QUOTTERY_CREATED_EVENT = 100001;
constexpr uint64 QUOTTERY_PUBLISH_RESULT = 100002;
constexpr uint64 QUOTTERY_RESOLVE_DISPUTE = 100003;
constexpr uint64 QUOTTERY_FINALIZE_EVENT = 100004;
constexpr uint64 QUOTTERY_UPDATED_NEW_GOV_PARAMS = 100005;
constexpr uint64 QUOTTERY_UPDATED_NEW_DISCOUNT_FEE = 100006;
constexpr uint64 QUOTTERY_UPDATED_NEW_HOSTING_FEE = 100007;
constexpr uint64 QUOTTERY_ARCHIVE_EVENT = 100008;
constexpr uint64 QUOTTERY_MATCH_TYPE_0 = 100009; // A0,B0;
constexpr uint64 QUOTTERY_MATCH_TYPE_1 = 100010; // A1,B1;
constexpr uint64 QUOTTERY_MATCH_TYPE_2 = 100011; // A0,A1;
constexpr uint64 QUOTTERY_MATCH_TYPE_3 = 100012; // B0,B1;
constexpr uint64 QUOTTERY_ADD_BID = 100013;
constexpr uint64 QUOTTERY_ADD_ASK = 100014;
constexpr uint64 QUOTTERY_CREATED_EVENT_GROUP = 100015;
constexpr uint64 QUOTTERY_ADDED_MARKET_TO_EVENT_GROUP = 100016;
constexpr uint64 QUOTTERY_OPENED_EVENT_GROUP = 100017;
constexpr uint64 QUOTTERY_PUBLISHED_EVENT_GROUP_RESULT = 100018;
constexpr uint64 QUOTTERY_RESOLVED_EVENT_GROUP_DISPUTE = 100019;
constexpr uint64 QUOTTERY_FINALIZED_EVENT_GROUP = 100020;
constexpr uint64 QUOTTERY_ARCHIVED_EVENT_GROUP = 100021;
constexpr uint64 QUOTTERY_DISPUTED_EVENT_GROUP = 100022;
constexpr uint64 QUOTTERY_CANCELED_EVENT_GROUP = 100023;
constexpr uint64 QUOTTERY_CONVERTED_NEG_RISK_POSITIONS = 100024;
constexpr uint64 QUOTTERY_REVERSED_NEG_RISK_POSITIONS = 100025;
constexpr uint64 QUOTTERY_BOUGHT_NEG_RISK_POSITION = 100026;
constexpr uint64 QUOTTERY_SOLD_NEG_RISK_POSITION = 100027;
constexpr uint64 QUOTTERY_MATCHED_EVENT_GROUP_MINT = 100028;
constexpr uint64 QUOTTERY_MATCHED_EVENT_GROUP_MERGE = 100029;
constexpr uint64 QUOTTERY_ASK_BIT = 0;
constexpr uint64 QUOTTERY_BID_BIT = 1;
constexpr uint64 QUOTTERY_EID_MASK = 0x3FFFFFFFFFFFFFFFULL; // (2^62 - 1);
constexpr uint64 QUOTTERY_MAX_AMOUNT = 2000000000000LL; // 2 trillion;
constexpr sint8 QUOTTERY_RESULT_NOT_SET = -1;
constexpr sint8 QUOTTERY_RESULT_NO = 0;
constexpr sint8 QUOTTERY_RESULT_YES = 1;

constexpr uint64 QUOTTERY_MAX_MARKETS_PER_EVENT_GROUP = 64;
constexpr uint64 QUOTTERY_MAX_NEG_RISK_ORDER_FILLS = 256;
constexpr uint8 QUOTTERY_EVENT_GROUP_MODE_INDEPENDENT = 0;
constexpr uint8 QUOTTERY_EVENT_GROUP_MODE_EXCLUSIVE_ONE = 1;
constexpr uint8 QUOTTERY_EVENT_GROUP_STATUS_DRAFT = 0;
constexpr uint8 QUOTTERY_EVENT_GROUP_STATUS_OPEN = 1;
constexpr uint8 QUOTTERY_EVENT_GROUP_STATUS_RESOLVING = 2;
constexpr uint8 QUOTTERY_EVENT_GROUP_STATUS_FINALIZED = 3;

struct QUOTTERY2
{
};

struct QUOTTERY : public ContractBase
{
public:
    // logging enum
    struct QuotteryLogger
    {
        uint32 _contractIndex;
        uint32 _type; // Assign a random unique (per contract) number to distinguish messages of different types
        // Other data go here
        sint8 _terminator; // Only data before "_terminator" are logged
    };

    // logging with a number
    struct QuotteryLoggerWithData
    {
        uint32 _contractIndex;
        uint32 _type; // Assign a random unique (per contract) number to distinguish messages of different types
        id data;
        // Other data go here
        sint8 _terminator; // Only data before "_terminator" are logged
    };

    struct QuotteryTradeLogger
    {
        uint32 _contractIndex;
        uint32 _type; // Assign a random unique (per contract) number to distinguish messages of different types
        id A, B;
        uint64 eid;
        uint64 option;
        uint64 padding0;
        uint64 padding1;
        sint64 amount;
        sint64 price0;
        sint64 price1;
        sint8 _terminator; // Only data before "_terminator" are logged
    };

    struct QuotteryNegRiskConversionLogger
    {
        uint32 _contractIndex;
        uint32 _type;
        id trader;
        uint64 eventGroupId;
        uint64 noMarketMask;
        sint64 amount;
        sint64 collateralOut;
        sint8 _terminator;
    };

    struct QuotteryNegRiskRouteLogger
    {
        uint32 _contractIndex;
        uint32 _type;
        id trader;
        uint64 eventGroupId;
        uint64 targetMarketId;
        sint64 amount;
        sint64 grossAmount;
        sint64 collateralAmount;
        uint64 orderFillCount;
        sint8 _terminator;
    };

    struct QuotteryEventGroupTradeLogger
    {
        uint32 _contractIndex;
        uint32 _type;
        id trader;
        uint64 eventGroupId;
        uint64 marketId;
        sint64 amount;
        sint64 price;
        sint8 _terminator;
    };
    /**************************************/
    /********INPUT AND OUTPUT STRUCTS******/
    /**************************************/
    struct BasicInfo_input
    {
    };
    struct BasicInfo_output
    {
        uint64 operationFee; // 1000 is 100%
        uint64 shareholderFee;
        uint64 burnFee; // percentage
        uint64 nIssuedEvent; // number of issued event
        uint64 shareholdersRevenue;
        uint64 operationRevenue;
        uint64 burnedAmount;
        uint64 mFeePerDay;
        uint64 antiSpamAmount;
        uint64 depositAmountForDispute;
        id gameOperator;
        uint64 nIssuedEventGroup;
    };

    /**************************************/
    /************CONTRACT STATES***********/
    /**************************************/
    /*
    * QTRY V2
    */

    struct QtryEventInfo
    {
        uint64 eid;
        DateAndTime openDate; // submitted date
        DateAndTime endDate; // stop receiving result from OPs

        /*256 sint8s to describe*/
        Array<id, 4> desc;
        /*128 sint8s to describe option */
        Array<id, 2> option0Desc;
        Array<id, 2> option1Desc;
    };

    // A user-facing event groups one or more binary markets. Existing
    // QtryEventInfo records remain the independently traded market units.
    struct QtryEventGroupInfo
    {
        uint64 eventGroupId;
        DateAndTime createdDate;
        DateAndTime openedDate;
        Array<id, 4> desc;
        uint16 expectedMarketCount;
        uint16 marketCount;
        uint16 finalizedMarketCount;
        uint16 archivedMarketCount;
        uint8 mode;
        uint8 status;
    };

    struct QtryEventGroupMarkets
    {
        Array<uint64, QUOTTERY_MAX_MARKETS_PER_EVENT_GROUP> marketIds;
    };

    struct QtryMarketGroupLink
    {
        uint64 eventGroupId;
        uint16 marketIndex;
    };
    struct DepositInfo
    {
        id pubkey;
        sint64 amount;
    };
    struct DisputeResolveInfo
    {
        Array<uint16, 1024> epochData;
        Array<sint8, 1024> voteData;
    };
    // qtry-v2: orders array
    struct QtryOrder
    {
        id entity;
        sint64 amount;
    };

    struct OrderInfo
    {
        uint64 eid;
        uint64 option; // 0 or 1
        uint64 tradeBit; // 0 ask, 1 bid
    };

    struct DetailedOrderInfo
    {
        QtryOrder qo;
        uint64 eid;
        sint64 price;
        sint64 index;
        bit justAdded;
    };
    // gov struct
    struct QtryGOV // votable by mQTRYGOVIdentifier holders
    {
        uint64 mShareHolderFee;
        uint64 mBurnFee;
        uint64 mOperationFee;
        sint64 mFeePerDay;
        sint64 mDepositAmountForDispute;
        id mOperationId;
        bool isValid()
        {
            return mShareHolderFee < QUOTTERY_PERCENT_DENOMINATOR &&
                mBurnFee < QUOTTERY_PERCENT_DENOMINATOR &&
                mOperationFee < QUOTTERY_PERCENT_DENOMINATOR &&
                (mShareHolderFee + mBurnFee + mOperationFee) < QUOTTERY_PERCENT_DENOMINATOR &&
                mOperationId != NULL_ID;
        }
    };

    // holders can submit a new set of params, if 2/3 agree with the same config, that will be used in next epoch
    struct proposalVoter
    {
        id publicKey;
        QtryGOV proposed;
        uint64 amountOfShares;
        uint16 proposedEpoch;
    };
    // buffers for calculating at the end of epoch
    struct GovHolder
    {
        id publicKey;
        sint64 amount;
    };

    struct StateData
    {
        HashMap<uint64, QtryEventInfo, QUOTTERY_MAX_CONCURRENT_EVENT> mEventInfo;
        HashMap<uint64, sint8, QUOTTERY_MAX_CONCURRENT_EVENT> mEventResult; // NOT_SET: -1 , NO: 0, 1: YES: 1
        HashMap<uint64, uint32, QUOTTERY_MAX_CONCURRENT_EVENT> mEventResultPublishTickTime; // a tick tracker to know when the result was published
        HashMap<uint64, bit, QUOTTERY_MAX_CONCURRENT_EVENT> mEventFinalFlag; // flag if the event is already finalized (result is set and pass dispute window) 
        HashMap<uint64, DepositInfo, QUOTTERY_MAX_CONCURRENT_EVENT> mDisputeInfo;
        HashMap<uint64, DisputeResolveInfo, QUOTTERY_MAX_CONCURRENT_EVENT> mDisputeResolver;
        HashMap<uint64, DepositInfo, QUOTTERY_MAX_CONCURRENT_EVENT> mGODepositInfo;
        HashMap<id, QtryOrder, QUOTTERY_MAX_NUMBER_OF_USER> mPositionInfo;
        Collection<QtryOrder, 2097152 * X_MULTIPLIER> mABOrders;

        Array<uint64, QUOTTERY_MAX_CONCURRENT_EVENT> mRecentActiveEvent;

        // other stats
        uint64 mCurrentEventID;

        uint64 mShareholdersRevenue;
        uint64 mDistributedShareholdersRevenue;

        uint64 mOperationRevenue;
        uint64 mDistributedOperationRevenue;
        uint64 mBurnedAmount;
        Asset mQUSDIdentifier;
        Asset mQTRYGOVIdentifier;
        sint64 wholeSharePrice;
        QtryGOV mQtryGov;
        struct OperationParams // can be changed by operation team
        {
            HashMap<id, uint64, 8192 * X_MULTIPLIER> discountedFeeForUsers; // for professional market maker
            sint64 mAntiSpamAmount; // in QUs
        } mOperationParams;
        Array< proposalVoter, 1024> mGovVoters;
        HashMap<id, sint32, 1024> mVoteMap;
        Array<GovHolder, 1024> mGovArray;
        Array<sint64, 1024> mAccumulatedSum;

        // Event groups are appended to preserve the layout of all existing
        // Quottery state fields during contract-state migration.
        HashMap<uint64, QtryEventGroupInfo, QUOTTERY_MAX_CONCURRENT_EVENT> mEventGroupInfo;
        HashMap<uint64, QtryEventGroupMarkets, QUOTTERY_MAX_CONCURRENT_EVENT> mEventGroupMarkets;
        HashMap<uint64, QtryMarketGroupLink, QUOTTERY_MAX_CONCURRENT_EVENT> mMarketGroupLink;
        HashMap<uint64, sint8, QUOTTERY_MAX_CONCURRENT_EVENT> mEventGroupResult;
        HashMap<uint64, uint32, QUOTTERY_MAX_CONCURRENT_EVENT> mEventGroupResultPublishTickTime;
        HashMap<uint64, DepositInfo, QUOTTERY_MAX_CONCURRENT_EVENT> mEventGroupDisputeInfo;
        HashMap<uint64, DisputeResolveInfo, QUOTTERY_MAX_CONCURRENT_EVENT> mEventGroupDisputeResolver;
        HashMap<uint64, DepositInfo, QUOTTERY_MAX_CONCURRENT_EVENT> mEventGroupGODepositInfo;
        HashMap<uint64, bit, QUOTTERY_MAX_CONCURRENT_EVENT> mEventGroupDisputeResolved;
        uint64 mCurrentEventGroupID;
    };


    /**************************************/
    /************UTIL FUNCTIONS************/
    /**************************************/
protected:
    inline static uint64 orderKey(uint64 option, uint64 tradeBit, uint64 eid)
    {
        return ((option << 63) | (tradeBit << 62) | (eid & QUOTTERY_EID_MASK));
    }
    inline static uint64 posKey(uint64 option, uint64 eid)
    {
        return (((uint64)(option) << 63) | (eid & QUOTTERY_EID_MASK));
    }
    inline static uint64 divUp(uint64 a, uint64 b)
    {
        return div((a + b - 1), b);
    }
    inline static sint32 min(sint32 a, sint32 b)
    {
        return (a < b) ? a : b;
    }

    inline static sint64 min(sint64 a, sint64 b)
    {
        return (a < b) ? a : b;
    }

    /**
     * @brief Helper to construct a unique key for the order book.
     * Packs option, trade type (ask/bid), and event ID into a single uint64.
     */
    static id MakeOrderKey(const uint64 eid, const uint64 option, const uint64 tradeBit, id r)
    {
        r.u64._0 = 0;
        r.u64._1 = 0;
        r.u64._2 = 0;
        r.u64._3 = orderKey(option, tradeBit, eid);
        return r;
    }

    /**
     * @brief Helper to construct a unique key for a user's position.
     * Packs the user's ID with the option and event ID.
     */
    static id MakePosKey(id r, const uint64 eid, const uint64 option)
    {
        r.u64._3 = posKey(option, eid);
        return r;
    }

    /**
     * @brief Checks if an option is valid (0 or 1).
     */
    static bool isOptionValid(uint64 option)
    {
        return (option == 0 || option == 1);
    }

    /**
     * @brief Checks if an amount is within valid contract limits.
     */
    static bool isAmountValid(uint64 amount)
    {
        return amount > 0 && amount < QUOTTERY_MAX_AMOUNT;
    }

    /**
     * @brief Checks if a price is within valid contract limits.
     */
    static bool isPriceValid(sint64 price, sint64 wholeSharePrice)
    {
        return price > 0 && price <= wholeSharePrice;
    }

    struct ValidatePosition_input
    {
        id uid;
        uint64 eventId;
        uint64 option; // 0 or 1
        sint64 amount;
    };
    struct ValidatePosition_output
    {
        bit isValid;
    };
    struct ValidatePosition_locals
    {
        id key;
        QtryOrder qo;
    };

    struct ValidateEvent_input
    {
        uint64 eventId;
    };
    struct ValidateEvent_output
    {
        sint64 isValid;
    };
    struct ValidateEvent_locals
    {
        QtryEventInfo qei;
        QtryMarketGroupLink marketGroupLink;
        QtryEventGroupInfo eventGroupInfo;
        DateAndTime dt;
        bool status;
    };

    /**
     * @brief Checks if an event is valid for trading (exists and is within its trading window).
     * @param eventId The unique identifier of the event.
     * @return 1 if the event is valid for trading, 0 otherwise.
     */
    PRIVATE_FUNCTION_WITH_LOCALS(ValidateEvent)
    {
        output.isValid = 0;
        locals.status = state.get().mEventInfo.get(input.eventId, locals.qei);
        if (!locals.status)
        {
            return;
        }

        // Legacy standalone markets have no group link and retain their
        // original lifecycle. Grouped markets cannot trade while their
        // parent event is still being assembled.
        if (state.get().mMarketGroupLink.get(input.eventId, locals.marketGroupLink))
        {
            if (!state.get().mEventGroupInfo.get(locals.marketGroupLink.eventGroupId, locals.eventGroupInfo))
            {
                return;
            }
            if (locals.eventGroupInfo.status != QUOTTERY_EVENT_GROUP_STATUS_OPEN)
            {
                return;
            }
        }

        locals.dt = qpi.now();

        if (locals.dt < locals.qei.openDate) // now < open_date
        {
            return;
        }

        if (locals.dt > locals.qei.endDate) // now > end_date
        {
            return;
        }
        output.isValid = 1;
        return;
    }
    /**
     * @brief Validates that a user owns a sufficient amount of a specific position (shares).
     * @param uid The user's ID.
     * @param eventId The event ID.
     * @param option The option (0 or 1).
     * @param amount The amount to check for.
     * @return 1 if the user's position is sufficient, 0 otherwise.
     */
    PRIVATE_FUNCTION_WITH_LOCALS(ValidatePosition)
    {
        output.isValid = 0;
        locals.key = MakePosKey(input.uid, input.eventId, input.option);
        if (!state.get().mPositionInfo.get(locals.key, locals.qo))
        {
            // doesn't exist
            return;
        }
        if (locals.qo.amount < input.amount)
        {
            // less than owned amount
            return;
        }
        output.isValid = 1;
        return;
    }

    struct UpdatePosition_input
    {
        id uid;
        OrderInfo oi;
        sint64 amountChange; // positive => increase, negative => decrease
    };
    struct UpdatePosition_output
    {
        bit ok;
    };
    struct UpdatePosition_locals
    {
        id key;
        QtryOrder value;
    };

    // Update position of an user - must call validation before calling this
    PRIVATE_PROCEDURE_WITH_LOCALS(UpdatePosition)
    {
        output.ok = 0;

        locals.key = MakePosKey(input.uid, input.oi.eid, input.oi.option);

        if (!state.get().mPositionInfo.get(locals.key, locals.value))
        {
            if (input.amountChange >= 0)
            {
                locals.value.amount = input.amountChange;
                locals.value.entity = input.uid;
                state.mut().mPositionInfo.set(locals.key, locals.value);
            }
            else
            {
                // invalid state: cannot apply negative change to non-existent position
                output.ok = 0;
                return;
            }
        }
        else
        {
            if ((input.amountChange > 0 && locals.value.amount > INT64_MAX - input.amountChange) ||
                (input.amountChange < 0 && locals.value.amount < -input.amountChange))
            {
                output.ok = 0;
                return;
            }
            locals.value.amount += input.amountChange;
            if (locals.value.amount > 0)
            {
                state.mut().mPositionInfo.set(locals.key, locals.value);
            }
            else if (locals.value.amount == 0)
            {
                state.mut().mPositionInfo.removeByKey(locals.key);
            }
            else
            {
                // invalid state: position amount went negative
                output.ok = 0;
                return;
            }
        }
        output.ok = 1;
    }

    struct RewardTransfer_input
    {
        id receiver;
        uint64 eid;
        sint64 amount;
        bit needChargeFee;
    };

    struct RewardTransfer_output
    {
        bit ok;
    };

    struct RewardTransfer_locals
    {
        sint64 total, feeTotal, fee;
        uint64 rate, afterDiscountRate, amountWithDiscount;
    };

    /**
     * @brief Handles all outgoing transfers from the contract. It calculates and deducts fees
     * for shareholders, operations, creators, and oracles before sending the net amount.
     * @param receiver The recipient of the funds.
     * @param eid The associated event ID for fee calculation.
     * @param amount The gross amount to transfer.
     * @param needChargeFee If true, fees are calculated and deducted.
     */
    PRIVATE_PROCEDURE_WITH_LOCALS(RewardTransfer)
    {
        output.ok = false;
        if (input.amount <= 0 || input.amount >= MAX_AMOUNT) return;
        if (input.receiver == NULL_ID) return;
        locals.total = input.amount;
        locals.feeTotal = 0;

        if (input.needChargeFee)
        {
            // get discounted rate for this user
            locals.rate = 0;
            if (state.get().mOperationParams.discountedFeeForUsers.contains(input.receiver))
            {
                state.get().mOperationParams.discountedFeeForUsers.get(input.receiver, locals.rate);
            }
            locals.afterDiscountRate = QUOTTERY_PERCENT_DENOMINATOR - locals.rate;

            if (locals.afterDiscountRate)
            {
                locals.amountWithDiscount = smul((uint64)input.amount, locals.afterDiscountRate);
                // shareholders
                locals.fee = div(smul(locals.amountWithDiscount, state.get().mQtryGov.mShareHolderFee), QUOTTERY_PERCENT_DENOMINATOR * QUOTTERY_PERCENT_DENOMINATOR);
                locals.feeTotal += locals.fee;
                state.mut().mShareholdersRevenue += locals.fee;

                // operation team
                locals.fee = div(smul(locals.amountWithDiscount, state.get().mQtryGov.mOperationFee), QUOTTERY_PERCENT_DENOMINATOR * QUOTTERY_PERCENT_DENOMINATOR);
                locals.feeTotal += locals.fee;
                state.mut().mOperationRevenue += locals.fee;
            }
        }

        if (qpi.transferShareOwnershipAndPossession(state.get().mQUSDIdentifier.assetName, state.get().mQUSDIdentifier.issuer, SELF, SELF, locals.total - locals.feeTotal, input.receiver) < 0)
        {
            return;
        }
        output.ok = true;
    }

    struct MatchingOrders_input
    {
        uint64 eventId;
        uint64 justAddedIndex;
    };

    struct MatchingOrders_output
    {
        bit matched;
    };

    struct MatchingOrders_locals
    {
        /*
        * A0 => lowest amount of QUs for selling option 0
        * A1 => lowest amount of QUs for selling option 1
        * B0 => highest amount of QUs they bid for option 0
        * B1 => highest amount of QUs they bid for option 1
        */
        DetailedOrderInfo A0, A1, B0, B1;

        sint64 matchedAmount;
        sint64 matchedPrice;
        sint64 matchedPrice0;
        sint64 matchedPrice1;

        id key, r;

        RewardTransfer_input ti;
        RewardTransfer_output to;

        UpdatePosition_input upi;
        UpdatePosition_output upo;

        QuotteryTradeLogger log;
    };

    // only invoke when recently added order is any of (A0, A1, B0, B1)
    PRIVATE_PROCEDURE_WITH_LOCALS(MatchingOrders)
    {
        /*Initialize data*/
        output.matched = 0;
        locals.key = MakeOrderKey(input.eventId, 0, QUOTTERY_ASK_BIT, locals.r);
        locals.A0.index = state.mut().mABOrders.headIndex(locals.key);

        locals.key = MakeOrderKey(input.eventId, 1, QUOTTERY_ASK_BIT, locals.r);
        locals.A1.index = state.mut().mABOrders.headIndex(locals.key);

        locals.key = MakeOrderKey(input.eventId, 0, QUOTTERY_BID_BIT, locals.r);
        locals.B0.index = state.mut().mABOrders.headIndex(locals.key);

        locals.key = MakeOrderKey(input.eventId, 1, QUOTTERY_BID_BIT, locals.r);
        locals.B1.index = state.mut().mABOrders.headIndex(locals.key);

        if (locals.A0.index != NULL_INDEX)
        {
            locals.A0.qo = state.mut().mABOrders.element(locals.A0.index);
            locals.A0.price = -state.mut().mABOrders.priority(locals.A0.index);
            locals.A0.justAdded = (input.justAddedIndex == locals.A0.index);
        }
        if (locals.A1.index != NULL_INDEX)
        {
            locals.A1.qo = state.mut().mABOrders.element(locals.A1.index);
            locals.A1.price = -state.mut().mABOrders.priority(locals.A1.index);
            locals.A1.justAdded = (input.justAddedIndex == locals.A1.index);
        }
        if (locals.B0.index != NULL_INDEX)
        {
            locals.B0.qo = state.mut().mABOrders.element(locals.B0.index);
            locals.B0.price = state.mut().mABOrders.priority(locals.B0.index);
            locals.B0.justAdded = (input.justAddedIndex == locals.B0.index);
        }
        if (locals.B1.index != NULL_INDEX)
        {
            locals.B1.qo = state.mut().mABOrders.element(locals.B1.index);
            locals.B1.price = state.mut().mABOrders.priority(locals.B1.index);
            locals.B1.justAdded = (input.justAddedIndex == locals.B1.index);
        }

        // scenario 1: traditional matching
        // Option 0: ask match with bid
        if (locals.A0.price <= locals.B0.price && locals.A0.index != NULL_INDEX && locals.B0.index != NULL_INDEX)
        {
            // bid > ask
            if (locals.A0.justAdded)
            {
                locals.matchedPrice = locals.B0.price;
            }
            else
            {
                locals.matchedPrice = locals.A0.price;
            }
            locals.matchedAmount = min(locals.A0.qo.amount, locals.B0.qo.amount);
            locals.log = QuotteryTradeLogger{ 0, QUOTTERY_MATCH_TYPE_0, locals.A0.qo.entity, locals.B0.qo.entity, input.eventId, 0, 0, 0, locals.matchedAmount, locals.matchedPrice, 0, 0 };
            LOG_INFO(locals.log);

            locals.ti.amount = smul(locals.matchedPrice, locals.matchedAmount);
            locals.ti.eid = input.eventId;
            locals.ti.receiver = locals.A0.qo.entity;
            locals.ti.needChargeFee = 1;
            CALL(RewardTransfer, locals.ti, locals.to);
            if (!locals.to.ok) return;

            // add shares to B (A is already deducted when they do ask order)
            locals.upi.uid = locals.B0.qo.entity;
            locals.upi.amountChange = locals.matchedAmount;
            locals.upi.oi.eid = input.eventId;
            locals.upi.oi.option = 0;
            locals.upi.oi.tradeBit = QUOTTERY_ASK_BIT;
            CALL(UpdatePosition, locals.upi, locals.upo);

            if (locals.B0.justAdded && locals.B0.price > locals.matchedPrice)
            {
                // refund without charging fees
                locals.ti.amount = smul(locals.B0.price - locals.matchedPrice, locals.matchedAmount);
                locals.ti.eid = input.eventId;
                locals.ti.receiver = locals.B0.qo.entity;
                locals.ti.needChargeFee = 0;
                CALL(RewardTransfer, locals.ti, locals.to);
                if (!locals.to.ok) return;
            }

            output.matched = 1;
            // update order size
            locals.A0.qo.amount -= locals.matchedAmount;
            locals.B0.qo.amount -= locals.matchedAmount;
            if (locals.A0.qo.amount)
            {
                state.mut().mABOrders.replace(locals.A0.index, locals.A0.qo);
            }
            else
            {
                state.mut().mABOrders.remove(locals.A0.index);
            }

            // A0 maybe removed and change the index of B0
            locals.key = MakeOrderKey(input.eventId, 0, QUOTTERY_BID_BIT, locals.r);
            locals.B0.index = state.mut().mABOrders.headIndex(locals.key);

            if (locals.B0.qo.amount)
            {
                state.mut().mABOrders.replace(locals.B0.index, locals.B0.qo);
            }
            else
            {
                state.mut().mABOrders.remove(locals.B0.index);
            }
            return;
        }

        // Option 1: ask match with bid
        if (locals.A1.price <= locals.B1.price && locals.A1.index != NULL_INDEX && locals.B1.index != NULL_INDEX)
        {
            // bid > ask
            if (locals.A1.justAdded)
            {
                locals.matchedPrice = locals.B1.price;
            }
            else
            {
                locals.matchedPrice = locals.A1.price;
            }
            locals.matchedAmount = min(locals.A1.qo.amount, locals.B1.qo.amount);
            locals.log = QuotteryTradeLogger{ 0, QUOTTERY_MATCH_TYPE_1, locals.A1.qo.entity, locals.B1.qo.entity, input.eventId, 1, 0, 0, locals.matchedAmount, locals.matchedPrice, 0, 0 };
            LOG_INFO(locals.log);


            locals.ti.amount = smul(locals.matchedPrice, locals.matchedAmount);
            locals.ti.eid = input.eventId;
            locals.ti.receiver = locals.A1.qo.entity;
            locals.ti.needChargeFee = 1;
            CALL(RewardTransfer, locals.ti, locals.to);
            if (!locals.to.ok) return;

            // add shares to B (A is already deducted when they do ask order)
            locals.upi.uid = locals.B1.qo.entity;
            locals.upi.amountChange = locals.matchedAmount;
            locals.upi.oi.eid = input.eventId;
            locals.upi.oi.option = 1;
            locals.upi.oi.tradeBit = QUOTTERY_ASK_BIT;
            CALL(UpdatePosition, locals.upi, locals.upo);

            if (locals.B1.justAdded && locals.B1.price > locals.matchedPrice)
            {
                // refund without charging fees
                locals.ti.amount = smul(locals.B1.price - locals.matchedPrice, locals.matchedAmount);
                locals.ti.eid = input.eventId;
                locals.ti.receiver = locals.B1.qo.entity;
                locals.ti.needChargeFee = 0;
                CALL(RewardTransfer, locals.ti, locals.to);
                if (!locals.to.ok) return;
            }

            output.matched = 1;
            // update order size
            locals.A1.qo.amount -= locals.matchedAmount;
            locals.B1.qo.amount -= locals.matchedAmount;
            if (locals.A1.qo.amount)
            {
                state.mut().mABOrders.replace(locals.A1.index, locals.A1.qo);
            }
            else
            {
                state.mut().mABOrders.remove(locals.A1.index);
            }

            // A1 maybe removed and change the index of B1
            locals.key = MakeOrderKey(input.eventId, 1, QUOTTERY_BID_BIT, locals.r);
            locals.B1.index = state.mut().mABOrders.headIndex(locals.key);

            if (locals.B1.qo.amount)
            {
                state.mut().mABOrders.replace(locals.B1.index, locals.B1.qo);
            }
            else
            {
                state.mut().mABOrders.remove(locals.B1.index);
            }
            return;
        }

        // Scenario 2: MERGE - both want to sell
        // A0 and A1 want to exit => A0.price + A1.price < state.mut().wholeSharePrice
        if (locals.A0.price + locals.A1.price <= state.mut().wholeSharePrice && locals.A0.index != NULL_INDEX && locals.A1.index != NULL_INDEX)
        {
            if (locals.A0.justAdded)
            {
                locals.matchedPrice0 = state.mut().wholeSharePrice - locals.A1.price;
                locals.matchedPrice1 = locals.A1.price;
            }
            else
            {
                locals.matchedPrice0 = locals.A0.price;
                locals.matchedPrice1 = state.mut().wholeSharePrice - locals.A0.price;
            }
            locals.matchedAmount = min(locals.A0.qo.amount, locals.A1.qo.amount);
            locals.log = QuotteryTradeLogger{ 0, QUOTTERY_MATCH_TYPE_2, locals.A0.qo.entity, locals.A1.qo.entity, input.eventId, 2, 0, 0, locals.matchedAmount, locals.matchedPrice0, locals.matchedPrice1, 0 };
            LOG_INFO(locals.log);

            locals.ti.amount = smul(locals.matchedPrice0, locals.matchedAmount);
            locals.ti.eid = input.eventId;
            locals.ti.receiver = locals.A0.qo.entity;
            locals.ti.needChargeFee = 1;
            CALL(RewardTransfer, locals.ti, locals.to);
            if (!locals.to.ok) return;

            locals.ti.amount = smul(locals.matchedPrice1, locals.matchedAmount);
            locals.ti.eid = input.eventId;
            locals.ti.receiver = locals.A1.qo.entity;
            locals.ti.needChargeFee = 1;
            CALL(RewardTransfer, locals.ti, locals.to);
            if (!locals.to.ok) return;

            // the position is already deducted when adding ask orders, no need to do anything here about position shares

            output.matched = 1;

            // update order size
            locals.A0.qo.amount -= locals.matchedAmount;
            locals.A1.qo.amount -= locals.matchedAmount;
            if (locals.A0.qo.amount)
            {
                state.mut().mABOrders.replace(locals.A0.index, locals.A0.qo);
            }
            else
            {
                state.mut().mABOrders.remove(locals.A0.index);
            }

            // A0 maybe removed and change the index of A1
            locals.key = MakeOrderKey(input.eventId, 1, QUOTTERY_ASK_BIT, locals.r);
            locals.A1.index = state.mut().mABOrders.headIndex(locals.key);

            if (locals.A1.qo.amount)
            {
                state.mut().mABOrders.replace(locals.A1.index, locals.A1.qo);
            }
            else
            {
                state.mut().mABOrders.remove(locals.A1.index);
            }
            return;
        }

        // Scenario 3: MINT - both want to buy
        if (locals.B0.price + locals.B1.price >= state.mut().wholeSharePrice && locals.B0.index != NULL_INDEX && locals.B1.index != NULL_INDEX)
        {
            if (locals.B0.justAdded)
            {
                locals.matchedPrice0 = state.mut().wholeSharePrice - locals.B1.price;
                locals.matchedPrice1 = locals.B1.price;
            }
            else
            {
                locals.matchedPrice0 = locals.B0.price;
                locals.matchedPrice1 = state.mut().wholeSharePrice - locals.B0.price;
            }
            locals.matchedAmount = min(locals.B0.qo.amount, locals.B1.qo.amount);
            locals.log = QuotteryTradeLogger{ 0, QUOTTERY_MATCH_TYPE_3, locals.B0.qo.entity, locals.B1.qo.entity, input.eventId, 2, 0, 0, locals.matchedAmount, locals.matchedPrice0, locals.matchedPrice1, 0 };
            LOG_INFO(locals.log);
            // update position

            locals.upi.amountChange = locals.matchedAmount;
            locals.upi.oi.eid = input.eventId;
            locals.upi.oi.option = 0;
            locals.upi.uid = locals.B0.qo.entity;
            CALL(UpdatePosition, locals.upi, locals.upo);

            locals.upi.amountChange = locals.matchedAmount;
            locals.upi.oi.eid = input.eventId;
            locals.upi.oi.option = 1;
            locals.upi.uid = locals.B1.qo.entity;
            CALL(UpdatePosition, locals.upi, locals.upo);

            if (locals.B1.justAdded && locals.B1.price > locals.matchedPrice1)
            {
                // refund without charging fees
                locals.ti.amount = smul(locals.B1.price - locals.matchedPrice1, locals.matchedAmount);
                locals.ti.eid = input.eventId;
                locals.ti.receiver = locals.B1.qo.entity;
                locals.ti.needChargeFee = 0;
                CALL(RewardTransfer, locals.ti, locals.to);
                if (!locals.to.ok) return;
            }

            if (locals.B0.justAdded && locals.B0.price > locals.matchedPrice0)
            {
                // refund without charging fees
                locals.ti.amount = smul(locals.B0.price - locals.matchedPrice0, locals.matchedAmount);
                locals.ti.eid = input.eventId;
                locals.ti.receiver = locals.B0.qo.entity;
                locals.ti.needChargeFee = 0;
                CALL(RewardTransfer, locals.ti, locals.to);
                if (!locals.to.ok) return;
            }
            // update order size
            locals.B0.qo.amount -= locals.matchedAmount;
            locals.B1.qo.amount -= locals.matchedAmount;
            if (locals.B0.qo.amount)
            {
                state.mut().mABOrders.replace(locals.B0.index, locals.B0.qo);
            }
            else
            {
                state.mut().mABOrders.remove(locals.B0.index);
            }

            // B0 maybe removed and change the index of B1
            locals.key = MakeOrderKey(input.eventId, 1, QUOTTERY_BID_BIT, locals.r);
            locals.B1.index = state.mut().mABOrders.headIndex(locals.key);

            if (locals.B1.qo.amount)
            {
                state.mut().mABOrders.replace(locals.B1.index, locals.B1.qo);
            }
            else
            {
                state.mut().mABOrders.remove(locals.B1.index);
            }
            output.matched = 1;
            return;
        }
    }

    struct MatchingEventGroupOrders_input
    {
        uint64 eventGroupId;
        uint64 preferredMarketId;
        uint64 maxOrderFills;
        bit isBid;
    };

    struct MatchingEventGroupOrders_output
    {
        uint64 orderFillCount;
        uint64 matchCount;
    };

    struct MatchingEventGroupOrders_locals
    {
        uint16 i;
        uint16 pass;
        uint64 marketId;
        uint64 preferredMarketId;
        uint64 index;
        uint64 newPositionCount;
        uint64 contractBalance;
        sint64 price;
        sint64 actualPrice;
        sint64 sumPrice;
        sint64 matchedAmount;
        sint64 surplus;
        sint64 adjustment;
        sint64 transferAmount;
        sint64 totalTransferAmount;
        id key;
        id r;
        id positionKey;
        QtryOrder order;
        QtryOrder position;
        QtryEventInfo eventInfo;
        QtryEventGroupInfo eventGroupInfo;
        QtryEventGroupMarkets markets;
        DateAndTime now;
        RewardTransfer_input transferInput;
        RewardTransfer_output transferOutput;
        UpdatePosition_input updateInput;
        UpdatePosition_output updateOutput;
        QuotteryEventGroupTradeLogger tradeLog;
    };

    /**
     * @brief Matches one or more complete EXCLUSIVE_ONE YES sets.
     * Group mint consumes one YES bid from every market when their prices sum
     * to at least wholeSharePrice. Group merge consumes one YES ask from every
     * market when their prices sum to at most wholeSharePrice.
     *
     * The preferred market is treated as the taker for price improvement.
     * When mint surplus exceeds that bid, the remaining improvement is
     * distributed deterministically by market order. Every execution remains
     * within each participant's limit price.
     */
    PRIVATE_PROCEDURE_WITH_LOCALS(MatchingEventGroupOrders)
    {
        setMemory(output, 0);
        if (input.maxOrderFills == 0 || state.get().wholeSharePrice <= 0 ||
            !state.get().mEventGroupInfo.get(input.eventGroupId, locals.eventGroupInfo) ||
            locals.eventGroupInfo.mode != QUOTTERY_EVENT_GROUP_MODE_EXCLUSIVE_ONE ||
            locals.eventGroupInfo.status != QUOTTERY_EVENT_GROUP_STATUS_OPEN ||
            locals.eventGroupInfo.marketCount < 2 ||
            state.get().mEventGroupResult.contains(input.eventGroupId) ||
            !state.get().mEventGroupMarkets.get(input.eventGroupId, locals.markets))
        {
            return;
        }

        locals.preferredMarketId = locals.markets.marketIds.get(0);
        for (locals.i = 0; locals.i < locals.eventGroupInfo.marketCount; locals.i++)
        {
            if (locals.markets.marketIds.get(locals.i) == input.preferredMarketId)
            {
                locals.preferredMarketId = input.preferredMarketId;
                break;
            }
        }

        while (output.orderFillCount + locals.eventGroupInfo.marketCount <= input.maxOrderFills)
        {
            locals.sumPrice = 0;
            locals.matchedAmount = QUOTTERY_MAX_AMOUNT;
            locals.now = qpi.now();

            // Quote the best complete YES set at the current book heads.
            for (locals.i = 0; locals.i < locals.eventGroupInfo.marketCount; locals.i++)
            {
                locals.marketId = locals.markets.marketIds.get(locals.i);
                if (!state.get().mEventInfo.get(locals.marketId, locals.eventInfo) ||
                    locals.now < locals.eventInfo.openDate || locals.now > locals.eventInfo.endDate)
                {
                    return;
                }

                locals.key = MakeOrderKey(
                    locals.marketId,
                    QUOTTERY_RESULT_YES,
                    input.isBid ? QUOTTERY_BID_BIT : QUOTTERY_ASK_BIT,
                    locals.r);
                locals.index = state.get().mABOrders.headIndex(locals.key);
                if (locals.index == NULL_INDEX) return;

                locals.order = state.get().mABOrders.element(locals.index);
                locals.price = state.get().mABOrders.priority(locals.index);
                if (!input.isBid) locals.price = -locals.price;
                if (locals.order.amount <= 0 || locals.price < 0 ||
                    locals.sumPrice > MAX_AMOUNT - locals.price)
                {
                    return;
                }
                locals.sumPrice += locals.price;
                locals.matchedAmount = min(locals.matchedAmount, locals.order.amount);
            }

            if (locals.matchedAmount <= 0 ||
                (input.isBid && locals.sumPrice < state.get().wholeSharePrice) ||
                (!input.isBid && locals.sumPrice > state.get().wholeSharePrice) ||
                locals.matchedAmount > MAX_AMOUNT / state.get().wholeSharePrice)
            {
                return;
            }
            locals.totalTransferAmount = locals.matchedAmount * state.get().wholeSharePrice;

            if (input.isBid)
            {
                // Preflight every position update before refunding bid surplus.
                locals.newPositionCount = 0;
                for (locals.i = 0; locals.i < locals.eventGroupInfo.marketCount; locals.i++)
                {
                    locals.marketId = locals.markets.marketIds.get(locals.i);
                    locals.key = MakeOrderKey(
                        locals.marketId, QUOTTERY_RESULT_YES, QUOTTERY_BID_BIT, locals.r);
                    locals.index = state.get().mABOrders.headIndex(locals.key);
                    locals.order = state.get().mABOrders.element(locals.index);
                    locals.positionKey = MakePosKey(
                        locals.order.entity, locals.marketId, QUOTTERY_RESULT_YES);
                    if (state.get().mPositionInfo.get(locals.positionKey, locals.position))
                    {
                        if (locals.position.amount > INT64_MAX - locals.matchedAmount) return;
                    }
                    else
                    {
                        locals.newPositionCount++;
                    }
                }
                if (state.get().mPositionInfo.population() + locals.newPositionCount >
                    state.get().mPositionInfo.capacity())
                {
                    return;
                }

                locals.surplus = locals.sumPrice - state.get().wholeSharePrice;
                if (locals.surplus && locals.matchedAmount > MAX_AMOUNT / locals.surplus) return;
                locals.transferAmount = locals.surplus * locals.matchedAmount;
                locals.contractBalance = qpi.numberOfShares(
                    state.get().mQUSDIdentifier,
                    { SELF, SELF_INDEX },
                    { SELF, SELF_INDEX });
                if (locals.contractBalance < (uint64)locals.transferAmount) return;

                // Give price improvement to the preferred (taker) market first.
                // If it cannot absorb all surplus, continue in market order.
                for (locals.pass = 0; locals.pass < 2; locals.pass++)
                {
                    for (locals.i = 0; locals.i < locals.eventGroupInfo.marketCount; locals.i++)
                    {
                        locals.marketId = locals.markets.marketIds.get(locals.i);
                        if ((locals.pass == 0 && locals.marketId != locals.preferredMarketId) ||
                            (locals.pass == 1 && locals.marketId == locals.preferredMarketId))
                        {
                            continue;
                        }

                        locals.key = MakeOrderKey(
                            locals.marketId, QUOTTERY_RESULT_YES, QUOTTERY_BID_BIT, locals.r);
                        locals.index = state.get().mABOrders.headIndex(locals.key);
                        locals.order = state.get().mABOrders.element(locals.index);
                        locals.price = state.get().mABOrders.priority(locals.index);
                        locals.adjustment = min(locals.price, locals.surplus);
                        locals.actualPrice = locals.price - locals.adjustment;
                        locals.surplus -= locals.adjustment;

                        if (locals.adjustment)
                        {
                            locals.transferInput.receiver = locals.order.entity;
                            locals.transferInput.eid = locals.marketId;
                            locals.transferInput.amount = locals.adjustment * locals.matchedAmount;
                            locals.transferInput.needChargeFee = 0;
                            CALL(RewardTransfer, locals.transferInput, locals.transferOutput);
                            if (!locals.transferOutput.ok) return;
                        }

                        locals.updateInput.uid = locals.order.entity;
                        locals.updateInput.amountChange = locals.matchedAmount;
                        locals.updateInput.oi.eid = locals.marketId;
                        locals.updateInput.oi.option = QUOTTERY_RESULT_YES;
                        locals.updateInput.oi.tradeBit = QUOTTERY_BID_BIT;
                        CALL(UpdatePosition, locals.updateInput, locals.updateOutput);
                        if (!locals.updateOutput.ok) return;

                        locals.tradeLog = QuotteryEventGroupTradeLogger{
                            0, QUOTTERY_MATCHED_EVENT_GROUP_MINT, locals.order.entity,
                            input.eventGroupId, locals.marketId, locals.matchedAmount,
                            locals.actualPrice, 0
                        };
                        LOG_INFO(locals.tradeLog);

                        locals.order.amount -= locals.matchedAmount;
                        if (locals.order.amount)
                        {
                            state.mut().mABOrders.replace(locals.index, locals.order);
                        }
                        else
                        {
                            state.mut().mABOrders.remove(locals.index);
                        }
                    }
                }
            }
            else
            {
                // A complete YES set releases exactly one whole-share payout.
                locals.contractBalance = qpi.numberOfShares(
                    state.get().mQUSDIdentifier,
                    { SELF, SELF_INDEX },
                    { SELF, SELF_INDEX });
                if (locals.contractBalance < (uint64)locals.totalTransferAmount) return;

                locals.surplus = state.get().wholeSharePrice - locals.sumPrice;
                for (locals.i = 0; locals.i < locals.eventGroupInfo.marketCount; locals.i++)
                {
                    locals.marketId = locals.markets.marketIds.get(locals.i);
                    locals.key = MakeOrderKey(
                        locals.marketId, QUOTTERY_RESULT_YES, QUOTTERY_ASK_BIT, locals.r);
                    locals.index = state.get().mABOrders.headIndex(locals.key);
                    locals.order = state.get().mABOrders.element(locals.index);
                    locals.price = -state.get().mABOrders.priority(locals.index);
                    locals.actualPrice = locals.price;
                    if (locals.marketId == locals.preferredMarketId)
                    {
                        locals.actualPrice += locals.surplus;
                    }
                    if (locals.actualPrice &&
                        locals.matchedAmount > MAX_AMOUNT / locals.actualPrice)
                    {
                        return;
                    }

                    locals.transferInput.receiver = locals.order.entity;
                    locals.transferInput.eid = locals.marketId;
                    locals.transferInput.amount = locals.actualPrice * locals.matchedAmount;
                    locals.transferInput.needChargeFee = 1;
                    CALL(RewardTransfer, locals.transferInput, locals.transferOutput);
                    if (!locals.transferOutput.ok) return;

                    locals.tradeLog = QuotteryEventGroupTradeLogger{
                        0, QUOTTERY_MATCHED_EVENT_GROUP_MERGE, locals.order.entity,
                        input.eventGroupId, locals.marketId, locals.matchedAmount,
                        locals.actualPrice, 0
                    };
                    LOG_INFO(locals.tradeLog);

                    locals.order.amount -= locals.matchedAmount;
                    if (locals.order.amount)
                    {
                        state.mut().mABOrders.replace(locals.index, locals.order);
                    }
                    else
                    {
                        state.mut().mABOrders.remove(locals.index);
                    }
                }
            }

            output.orderFillCount += locals.eventGroupInfo.marketCount;
            output.matchCount++;
        }
    }

public:
    struct GetEventInfo_input
    {
        uint64 eventId;
    };
    struct GetEventInfo_output
    {
        QtryEventInfo qei;
        sint32 resultByGO; // NOT_SET: -1 , NO: 0, 1: YES: 1
        uint32 publishTickTime; // ignore if not set result. if result is set and 
        // publishTickTime is max uint32 then this event is already finalized
        DepositInfo disputerInfo; // NULL if no dispute
        uint32 computorsVote0;
        uint32 computorsVote1;
    };

    struct GetEventInfo_locals
    {
        sint8 result;
        DisputeResolveInfo dri;
        sint32 i;
    };
    /**
     * @param eventId
     * @return meta data of a event and its current state
     */
    PUBLIC_FUNCTION_WITH_LOCALS(GetEventInfo)
    {
        setMemory(output.qei, 0);
        state.get().mEventInfo.get(input.eventId, output.qei);
        state.get().mEventResult.get(input.eventId, locals.result);
        state.get().mEventResultPublishTickTime.get(input.eventId, output.publishTickTime);
        output.resultByGO = (sint32)locals.result; // for padding
        if (state.get().mDisputeInfo.contains(input.eventId))
        {
            state.get().mDisputeInfo.get(input.eventId, output.disputerInfo);
            state.get().mDisputeResolver.get(input.eventId, locals.dri);
            for (locals.i = 0; locals.i < NUMBER_OF_COMPUTORS; locals.i++)
            {
                if (locals.dri.epochData.get(locals.i) == qpi.epoch())
                {
                    if (locals.dri.voteData.get(locals.i) == 0) output.computorsVote0++;
                    if (locals.dri.voteData.get(locals.i) == 1) output.computorsVote1++;
                }
            }
        }
        else
        {
            output.disputerInfo.pubkey = NULL_ID;
            output.disputerInfo.amount = 0;
        }
        if (locals.result != QUOTTERY_RESULT_NOT_SET && state.get().mEventFinalFlag.contains(input.eventId))
        {
            output.publishTickTime = 0xffffffffu;
        }
    }

    struct GetEventInfoBatch_input
    {
        Array<uint64, 64> eventIds;
    };
    struct GetEventInfoBatch_output
    {
        Array<QtryEventInfo, 64> aqei;
    };

    struct GetEventInfoBatch_locals
    {
        uint64 i;
        QtryEventInfo qei;
    };

    /**
     * @brief Retrieves the metadata for 64 specific events.
     * @param array of eventId
     * @return The array of QtryEventInfo struct containing the event's details.
     */
    PUBLIC_FUNCTION_WITH_LOCALS(GetEventInfoBatch)
    {
        setMemory(output.aqei, 0);
        for (locals.i = 0; locals.i < 64; locals.i++)
        {
            if (state.get().mEventInfo.get(input.eventIds.get(locals.i), locals.qei))
            {
                output.aqei.set(locals.i, locals.qei);
            }
        }
    }

    struct GetEventGroup_input
    {
        uint64 eventGroupId;
    };
    struct GetEventGroup_output
    {
        QtryEventGroupInfo eventGroupInfo;
        QtryEventGroupMarkets markets;
        sint32 winningMarketIndex;
        uint64 winningMarketId;
        uint32 publishTickTime;
        DepositInfo disputerInfo;
        bit exists;
    };
    struct GetEventGroup_locals
    {
        sint8 winningMarketIndex;
    };

    PUBLIC_FUNCTION_WITH_LOCALS(GetEventGroup)
    {
        setMemory(output, 0);
        output.winningMarketIndex = QUOTTERY_RESULT_NOT_SET;
        if (!state.get().mEventGroupInfo.get(input.eventGroupId, output.eventGroupInfo))
        {
            return;
        }
        state.get().mEventGroupMarkets.get(input.eventGroupId, output.markets);
        if (state.get().mEventGroupResult.get(input.eventGroupId, locals.winningMarketIndex))
        {
            output.winningMarketIndex = locals.winningMarketIndex;
            output.winningMarketId = output.markets.marketIds.get(locals.winningMarketIndex);
        }
        state.get().mEventGroupResultPublishTickTime.get(input.eventGroupId, output.publishTickTime);
        state.get().mEventGroupDisputeInfo.get(input.eventGroupId, output.disputerInfo);
        output.exists = 1;
    }

    struct GetMarketEventGroup_input
    {
        uint64 marketId;
    };
    struct GetMarketEventGroup_output
    {
        QtryMarketGroupLink marketGroupLink;
        uint8 mode;
        uint8 status;
        bit exists;
    };
    struct GetMarketEventGroup_locals
    {
        QtryEventGroupInfo eventGroupInfo;
    };

    PUBLIC_FUNCTION_WITH_LOCALS(GetMarketEventGroup)
    {
        setMemory(output, 0);
        if (!state.get().mMarketGroupLink.get(input.marketId, output.marketGroupLink))
        {
            return;
        }
        if (!state.get().mEventGroupInfo.get(output.marketGroupLink.eventGroupId, locals.eventGroupInfo))
        {
            return;
        }
        output.mode = locals.eventGroupInfo.mode;
        output.status = locals.eventGroupInfo.status;
        output.exists = 1;
    }

    struct GetEventGroupInfoBatch_input
    {
        Array<uint64, 64> eventGroupIds;
    };
    struct GetEventGroupInfoBatch_output
    {
        Array<QtryEventGroupInfo, 64> eventGroupInfos;
        Array<sint8, 64> winningMarketIndices;
        Array<bit, 64> exists;
    };
    struct GetEventGroupInfoBatch_locals
    {
        uint64 i;
        QtryEventGroupInfo eventGroupInfo;
        sint8 winningMarketIndex;
    };

    PUBLIC_FUNCTION_WITH_LOCALS(GetEventGroupInfoBatch)
    {
        setMemory(output, 0);
        output.winningMarketIndices.setAll(QUOTTERY_RESULT_NOT_SET);
        for (locals.i = 0; locals.i < input.eventGroupIds.capacity(); locals.i++)
        {
            if (state.get().mEventGroupInfo.get(
                input.eventGroupIds.get(locals.i),
                locals.eventGroupInfo))
            {
                output.eventGroupInfos.set(locals.i, locals.eventGroupInfo);
                output.exists.set(locals.i, 1);
                if (state.get().mEventGroupResult.get(
                    input.eventGroupIds.get(locals.i),
                    locals.winningMarketIndex))
                {
                    output.winningMarketIndices.set(locals.i, locals.winningMarketIndex);
                }
            }
        }
    }

    struct AddToAskOrder_input
    {
        uint64 eventId;
        uint64 option;
        uint64 amount;
        sint64 price;
    };
    struct AddToAskOrder_output
    {
        sint64 status;
    };
    struct AddToAskOrder_locals
    {
        id key, r;
        // temp variables
        uint64 index;
        sint64 price;
        bit flag;
        bit mergedOrder;
        QtryEventInfo qei;
        QtryOrder order;
        QtryMarketGroupLink marketGroupLink;

        OrderInfo oi;

        ValidateEvent_input vei;
        ValidateEvent_output veo;

        ValidatePosition_input vpi;
        ValidatePosition_output vpo;

        MatchingOrders_input moi;
        MatchingOrders_output moo;

        MatchingEventGroupOrders_input groupMatchInput;
        MatchingEventGroupOrders_output groupMatchOutput;

        UpdatePosition_input upi;
        UpdatePosition_output upo;

        QuotteryLogger log;
        QuotteryTradeLogger tradeLog;
    };

    /**
     * @brief PUBLIC PROCEDURE
     * Allows a user to place an ask (sell) order for a position they own.
     * @param eventId The event to place the order on.
     * @param option The option (0 or 1) to sell.
     * @param amount The number of shares to sell.
     * @param price The price per share.
     */
    PUBLIC_PROCEDURE_WITH_LOCALS(AddToAskOrder)
    {
        if (state.get().mOperationParams.mAntiSpamAmount)
        {
            if (qpi.invocationReward() < state.get().mOperationParams.mAntiSpamAmount) return;
            if (qpi.invocationReward() > state.get().mOperationParams.mAntiSpamAmount) qpi.transfer(qpi.invocator(), qpi.invocationReward() - state.get().mOperationParams.mAntiSpamAmount);
        }
        locals.oi.eid = input.eventId;
        locals.oi.option = input.option;
        locals.oi.tradeBit = QUOTTERY_ASK_BIT;

        locals.vei.eventId = input.eventId;
        CALL(ValidateEvent, locals.vei, locals.veo);
        if (!locals.veo.isValid)
        {
            locals.log = QuotteryLogger{ 0, QUOTTERY_INVALID_EVENT_ID ,0 };
            LOG_WARNING(locals.log);
            return;
        }

        if (!state.get().mEventInfo.get(input.eventId, locals.qei))
        {
            return;
        }

        if (!isOptionValid(input.option) || !isAmountValid(input.amount) || !isPriceValid(input.price, state.get().wholeSharePrice))
        {
            return;
        }

        locals.vpi.uid = qpi.invocator();
        locals.vpi.amount = input.amount;
        locals.vpi.eventId = input.eventId;
        locals.vpi.option = input.option;
        CALL(ValidatePosition, locals.vpi, locals.vpo);
        if (!locals.vpo.isValid)
        {
            locals.log = QuotteryLogger{ 0, QUOTTERY_INVALID_POSITION, 0 };
            LOG_WARNING(locals.log);
            return;
        }

        {
            // deduct share
            locals.upi.uid = qpi.invocator();
            locals.upi.amountChange = -(sint64)(input.amount); // Negative to reduce balance
            locals.upi.oi.eid = input.eventId;
            locals.upi.oi.option = input.option;
            locals.upi.oi.tradeBit = QUOTTERY_ASK_BIT;
            CALL(UpdatePosition, locals.upi, locals.upo);
        }

        locals.tradeLog = QuotteryTradeLogger{ 0, QUOTTERY_ADD_ASK, qpi.invocator(), NULL_ID, input.eventId, input.option, 0, 0, (sint64)input.amount, (sint64)input.price, 0, 0 };
        LOG_INFO(locals.tradeLog);

        locals.key = MakeOrderKey(input.eventId, input.option, QUOTTERY_ASK_BIT, locals.r);
        locals.index = state.get().mABOrders.headIndex(locals.key, -input.price);
        locals.flag = false;
        locals.mergedOrder = false;

        // if there is exact 100% same order as this (same amount, trade bit, price, eventId):
        // if same user => replace new one
        // if diff user => add new one
        // final => exit
        while (locals.index != NULL_INDEX)
        {
            locals.order = state.get().mABOrders.element(locals.index);
            locals.price = -state.get().mABOrders.priority(locals.index);
            if (locals.price == input.price)
            {
                // this means there's another unmatched order with the same price
                locals.flag = true;
                if (locals.order.entity == qpi.invocator())
                {
                    // Aggregate the order, then run both binary and group matching.
                    locals.order.amount += input.amount;
                    state.mut().mABOrders.replace(locals.index, locals.order);
                    output.status = 1;
                    locals.mergedOrder = true;
                    break;
                }
                locals.index = state.get().mABOrders.nextElementIndex(locals.index);
            }
            else
            {
                break;
            }
        }

        if (!locals.mergedOrder)
        {
            locals.order.amount = input.amount;
            locals.order.entity = qpi.invocator();
            locals.index = state.mut().mABOrders.add(locals.key, locals.order, -input.price);
        }

        locals.moi.eventId = input.eventId;
        locals.moi.justAddedIndex = locals.index;
        locals.flag = 1;
        while (locals.flag)
        {
            // Drain all binary matches made possible by this order first.
            CALL(MatchingOrders, locals.moi, locals.moo);
            locals.flag = locals.moo.matched;
            if (locals.flag)
            {
                locals.key = MakeOrderKey(input.eventId, input.option, QUOTTERY_ASK_BIT, locals.r);
                locals.moi.justAddedIndex = state.get().mABOrders.headIndex(locals.key, -input.price);
            }
        }

        if (input.option == QUOTTERY_RESULT_YES &&
            state.get().mMarketGroupLink.get(input.eventId, locals.marketGroupLink))
        {
            locals.groupMatchInput.eventGroupId = locals.marketGroupLink.eventGroupId;
            locals.groupMatchInput.preferredMarketId = input.eventId;
            locals.groupMatchInput.maxOrderFills = QUOTTERY_MAX_NEG_RISK_ORDER_FILLS;
            locals.groupMatchInput.isBid = 0;
            CALL(MatchingEventGroupOrders, locals.groupMatchInput, locals.groupMatchOutput);
        }
        return;
    }

    struct RemoveAskOrder_input
    {
        uint64 eventId;
        uint64 option;
        uint64 amount;
        sint64 price;
    };
    struct RemoveAskOrder_output
    {
        sint64 status;
    };

    struct RemoveAskOrder_locals
    {
        id key, r;
        sint64 index;
        QtryEventInfo qei;
        QtryOrder order;
        sint64 price;
        sint64 amountToRemove;

        ValidateEvent_input vei;
        ValidateEvent_output veo;

        UpdatePosition_input upi;
        UpdatePosition_output upo;
    };

    /**
     * @brief PUBLIC PROCEDURE
     * Allows a user to remove an existing ask (sell) order from the order book.
     * @param eventId The event of the order.
     * @param option The option (0 or 1) of the order.
     * @param amount The amount to remove.
     * @param price The price of the order to remove.
     */
    PUBLIC_PROCEDURE_WITH_LOCALS(RemoveAskOrder)
    {
        if (state.get().mOperationParams.mAntiSpamAmount)
        {
            if (qpi.invocationReward() < state.get().mOperationParams.mAntiSpamAmount) return;
            if (qpi.invocationReward() > state.get().mOperationParams.mAntiSpamAmount) qpi.transfer(qpi.invocator(), qpi.invocationReward() - state.get().mOperationParams.mAntiSpamAmount);
        }

        locals.vei.eventId = input.eventId;
        CALL(ValidateEvent, locals.vei, locals.veo);
        if (!locals.veo.isValid)
        {
            return;
        }

        if (!state.get().mEventInfo.get(input.eventId, locals.qei))
        {
            return;
        }

        if (!isOptionValid(input.option) || !isAmountValid(input.amount) || !isPriceValid(input.price, state.get().wholeSharePrice))
        {
            return;
        }

        // No ValidatePosition here: shares were already deducted from position
        // when the ask order was placed. Validation is against the order book below.

        locals.key = MakeOrderKey(input.eventId, input.option, QUOTTERY_ASK_BIT, locals.r);
        locals.index = state.get().mABOrders.headIndex(locals.key, -input.price);

        // finding and modifying order
        while (locals.index != NULL_INDEX)
        {
            locals.order = state.get().mABOrders.element(locals.index);
            locals.price = -state.get().mABOrders.priority(locals.index);
            if (locals.price == input.price)
            {
                if (locals.order.entity == qpi.invocator())
                {
                    // clamp to actual order amount to prevent underflow
                    locals.amountToRemove = min(input.amount, locals.order.amount);
                    // same entity => update => exit
                    locals.order.amount -= locals.amountToRemove;
                    if (locals.order.amount)
                    {
                        state.mut().mABOrders.replace(locals.index, locals.order);
                    }
                    else
                    {
                        state.mut().mABOrders.remove(locals.index);
                    }
                    output.status = 1;
                    {
                        // add the position share back to mPositionInfo array
                        locals.upi.uid = qpi.invocator();
                        locals.upi.amountChange = locals.amountToRemove;
                        locals.upi.oi.eid = input.eventId;
                        locals.upi.oi.option = input.option;
                        locals.upi.oi.tradeBit = QUOTTERY_ASK_BIT;
                        CALL(UpdatePosition, locals.upi, locals.upo);
                    }
                    return;
                }
                locals.index = state.get().mABOrders.nextElementIndex(locals.index);
            }
            else
            {
                break;
            }
        }
    }

    struct RemoveBidOrder_input
    {
        uint64 eventId;
        uint64 option;
        uint64 amount;
        sint64 price;
    };
    struct RemoveBidOrder_output
    {
        sint64 status;
    };

    struct RemoveBidOrder_locals
    {
        id key, r;
        sint64 index;
        QtryEventInfo qei;
        QtryOrder order;
        sint64 price;
        sint64 amountToRemove;

        ValidateEvent_input vei;
        ValidateEvent_output veo;

        RewardTransfer_input rti;
        RewardTransfer_output rto;
    };

    /**
     * @brief PUBLIC PROCEDURE
     * Allows a user to remove an existing bid (buy) order and get a refund of their locked funds.
     * @param eventId The event of the order.
     * @param option The option (0 or 1) of the order.
     * @param amount The amount to remove.
     * @param price The price of the order to remove.
     */
    PUBLIC_PROCEDURE_WITH_LOCALS(RemoveBidOrder)
    {
        if (state.get().mOperationParams.mAntiSpamAmount)
        {
            if (qpi.invocationReward() < state.get().mOperationParams.mAntiSpamAmount) return;
            if (qpi.invocationReward() > state.get().mOperationParams.mAntiSpamAmount) qpi.transfer(qpi.invocator(), qpi.invocationReward() - state.get().mOperationParams.mAntiSpamAmount);
        }

        locals.vei.eventId = input.eventId;
        CALL(ValidateEvent, locals.vei, locals.veo);
        if (!locals.veo.isValid)
        {
            return;
        }

        if (!state.get().mEventInfo.get(input.eventId, locals.qei))
        {
            return;
        }

        if (!isOptionValid(input.option) || !isAmountValid(input.amount) || !isPriceValid(input.price, state.get().wholeSharePrice))
        {
            return;
        }

        locals.key = MakeOrderKey(input.eventId, input.option, QUOTTERY_BID_BIT, locals.r);
        locals.index = state.get().mABOrders.headIndex(locals.key, input.price);

        // finding and modifying order
        while (locals.index != NULL_INDEX)
        {
            locals.order = state.get().mABOrders.element(locals.index);
            locals.price = state.get().mABOrders.priority(locals.index);
            if (locals.price == input.price)
            {
                if (locals.order.entity == qpi.invocator())
                {
                    locals.amountToRemove = min(input.amount, locals.order.amount);
                    // same entity => update => exit
                    locals.order.amount -= locals.amountToRemove;
                    if (locals.order.amount)
                    {
                        state.mut().mABOrders.replace(locals.index, locals.order);
                    }
                    else
                    {
                        state.mut().mABOrders.remove(locals.index);
                    }
                    // refund
                    locals.rti.amount = smul(locals.amountToRemove, input.price);
                    locals.rti.eid = input.eventId;
                    locals.rti.needChargeFee = 0;
                    locals.rti.receiver = qpi.invocator();
                    CALL(RewardTransfer, locals.rti, locals.rto);
                    if (!locals.rto.ok) return;
                    output.status = 1;
                    return;
                }
                locals.index = state.get().mABOrders.nextElementIndex(locals.index);
            }
            else
            {
                break;
            }
        }
    }

    struct AddToBidOrder_input
    {
        uint64 eventId;
        uint64 option;
        sint64 amount;
        sint64 price;
    };
    struct AddToBidOrder_output
    {
        sint64 status;
    };
    struct AddToBidOrder_locals
    {
        id key, r;
        // temp variables
        uint64 index;
        sint64 price;
        uint64 userBalance;
        uint64 totalCost;
        bit flag;
        bit mergedOrder;
        QtryOrder order;
        QtryEventInfo qei;
        QtryMarketGroupLink marketGroupLink;

        ValidateEvent_input vei;
        ValidateEvent_output veo;

        MatchingOrders_input moi;
        MatchingOrders_output moo;

        MatchingEventGroupOrders_input groupMatchInput;
        MatchingEventGroupOrders_output groupMatchOutput;

        QuotteryTradeLogger log;
    };

    /**
     * @brief PUBLIC PROCEDURE
     * Allows a user to place a bid (buy) order, locking funds to back it.
     * Triggers the matching engine after the order is placed.
     * @param eventId The event to place the order on.
     * @param option The option (0 or 1) to buy.
     * @param amount The number of shares to buy.
     * @param price The price per share.
     */
    PUBLIC_PROCEDURE_WITH_LOCALS(AddToBidOrder)
    {
        if (state.get().mOperationParams.mAntiSpamAmount)
        {
            if (qpi.invocationReward() < state.get().mOperationParams.mAntiSpamAmount) return;
            if (qpi.invocationReward() > state.get().mOperationParams.mAntiSpamAmount) qpi.transfer(qpi.invocator(), qpi.invocationReward() - state.get().mOperationParams.mAntiSpamAmount);
        }

        locals.vei.eventId = input.eventId;
        CALL(ValidateEvent, locals.vei, locals.veo);
        if (!locals.veo.isValid)
        {
            return;
        }

        if (!state.get().mEventInfo.get(input.eventId, locals.qei))
        {
            return;
        }

        if (!isOptionValid(input.option) || !isAmountValid(input.amount) || !isPriceValid(input.price, state.get().wholeSharePrice))
        {
            return;
        }
        locals.userBalance = qpi.numberOfShares(state.get().mQUSDIdentifier, { qpi.invocator(), SELF_INDEX }, { qpi.invocator(), SELF_INDEX });
        locals.totalCost = smul(input.amount, input.price);
        // verify enough amount
        if (locals.totalCost > locals.userBalance)
        {
            return;
        }
        if (qpi.transferShareOwnershipAndPossession(state.get().mQUSDIdentifier.assetName, state.get().mQUSDIdentifier.issuer, qpi.invocator(), qpi.invocator(), locals.totalCost, SELF) < 0)
        {
            // critical error
            return;
        }

        locals.log = QuotteryTradeLogger{ 0, QUOTTERY_ADD_BID, qpi.invocator(), NULL_ID, input.eventId, input.option, 0, 0, (sint64)input.amount, (sint64)input.price, 0, 0 };
        LOG_INFO(locals.log);

        locals.key = MakeOrderKey(input.eventId, input.option, QUOTTERY_BID_BIT, locals.r);
        locals.index = state.get().mABOrders.headIndex(locals.key, input.price);
        locals.flag = false;
        locals.mergedOrder = false;

        // if there is exact 100% same order as this (same amount, trade bit, price, eventId):
        // if same user => replace new one
        // if diff user => add new one
        // final => exit
        while (locals.index != NULL_INDEX)
        {
            locals.order = state.get().mABOrders.element(locals.index);
            locals.price = state.get().mABOrders.priority(locals.index);
            if (locals.price == input.price)
            {
                // this means there's another unmatched order with the same price
                locals.flag = true;
                if (locals.order.entity == qpi.invocator())
                {
                    // Aggregate the order, then run both binary and group matching.
                    locals.order.amount += input.amount;
                    state.mut().mABOrders.replace(locals.index, locals.order);
                    output.status = 1;
                    locals.mergedOrder = true;
                    break;
                }
                locals.index = state.get().mABOrders.nextElementIndex(locals.index);
            }
            else
            {
                break;
            }
        }

        if (!locals.mergedOrder)
        {
            locals.order.amount = input.amount;
            locals.order.entity = qpi.invocator();
            locals.index = state.mut().mABOrders.add(locals.key, locals.order, input.price);
        }

        locals.moi.eventId = input.eventId;
        locals.moi.justAddedIndex = locals.index;
        locals.flag = 1;
        while (locals.flag)
        {
            // Drain all binary matches made possible by this order first.
            CALL(MatchingOrders, locals.moi, locals.moo);
            locals.flag = locals.moo.matched;
            if (locals.flag)
            {
                locals.key = MakeOrderKey(input.eventId, input.option, QUOTTERY_BID_BIT, locals.r);
                locals.moi.justAddedIndex = state.get().mABOrders.headIndex(locals.key, input.price);
            }
        }

        if (input.option == QUOTTERY_RESULT_YES &&
            state.get().mMarketGroupLink.get(input.eventId, locals.marketGroupLink))
        {
            locals.groupMatchInput.eventGroupId = locals.marketGroupLink.eventGroupId;
            locals.groupMatchInput.preferredMarketId = input.eventId;
            locals.groupMatchInput.maxOrderFills = QUOTTERY_MAX_NEG_RISK_ORDER_FILLS;
            locals.groupMatchInput.isBid = 1;
            CALL(MatchingEventGroupOrders, locals.groupMatchInput, locals.groupMatchOutput);
        }
        return;
    }

    struct Dispute_input
    {
        uint64 eventId;
    };
    struct Dispute_output
    {
    };

    struct Dispute_locals
    {
        sint8 result;
        DepositInfo di;
        QtryMarketGroupLink marketGroupLink;
        QtryEventGroupInfo eventGroupInfo;
    };

    // when users not agree with operator, they can dispute
    // the event will be resolved by computors
    PUBLIC_PROCEDURE_WITH_LOCALS(Dispute)
    {
        // deposit
        if (qpi.invocationReward() != state.get().mQtryGov.mDepositAmountForDispute)
        {
            if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
            return;
        }
        if (!state.get().mEventResult.get(input.eventId, locals.result))
        {
            if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
            return;
        }
        if (locals.result == QUOTTERY_RESULT_NOT_SET) // no result yet
        {
            if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
            return;
        }

        if (state.get().mMarketGroupLink.get(input.eventId, locals.marketGroupLink) &&
            state.get().mEventGroupInfo.get(locals.marketGroupLink.eventGroupId, locals.eventGroupInfo) &&
            locals.eventGroupInfo.mode == QUOTTERY_EVENT_GROUP_MODE_EXCLUSIVE_ONE)
        {
            if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
            return;
        }

        if (state.get().mDisputeInfo.contains(input.eventId)) // already being disputed by other users
        {
            if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
            return;
        }

        if (state.get().mEventFinalFlag.contains(input.eventId)) // already finalized
        {
            if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
            return;
        }

        locals.di.pubkey = qpi.invocator();
        locals.di.amount = state.get().mQtryGov.mDepositAmountForDispute;
        state.mut().mDisputeInfo.set(input.eventId, locals.di);
    }

    struct DisputeEventResult_input
    {
        uint64 eventGroupId;
    };
    struct DisputeEventResult_output
    {
        bit disputed;
    };
    struct DisputeEventResult_locals
    {
        sint32 i;
        sint8 result;
        uint32 publishTick;
        QtryEventGroupInfo eventGroupInfo;
        DepositInfo di;
        DisputeResolveInfo dri;
        QuotteryLoggerWithData log;
    };

    PUBLIC_PROCEDURE_WITH_LOCALS(DisputeEventResult)
    {
        if (qpi.invocationReward() != state.get().mQtryGov.mDepositAmountForDispute)
        {
            if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
            return;
        }
        if (!state.get().mEventGroupInfo.get(input.eventGroupId, locals.eventGroupInfo) ||
            locals.eventGroupInfo.mode != QUOTTERY_EVENT_GROUP_MODE_EXCLUSIVE_ONE ||
            locals.eventGroupInfo.status != QUOTTERY_EVENT_GROUP_STATUS_RESOLVING ||
            !state.get().mEventGroupResult.get(input.eventGroupId, locals.result) ||
            state.get().mEventGroupDisputeInfo.contains(input.eventGroupId) ||
            state.get().mEventGroupDisputeResolved.contains(input.eventGroupId))
        {
            if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
            return;
        }
        state.get().mEventGroupResultPublishTickTime.get(input.eventGroupId, locals.publishTick);
        if (locals.publishTick + QUOTTERY_DISPUTE_WINDOW <= qpi.tick())
        {
            if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
            return;
        }

        locals.di.pubkey = qpi.invocator();
        locals.di.amount = qpi.invocationReward();
        state.mut().mEventGroupDisputeInfo.set(input.eventGroupId, locals.di);
        for (locals.i = 0; locals.i < NUMBER_OF_COMPUTORS; locals.i++)
        {
            locals.dri.epochData.set(locals.i, 10000);
            locals.dri.voteData.set(locals.i, QUOTTERY_RESULT_NOT_SET);
        }
        state.mut().mEventGroupDisputeResolver.set(input.eventGroupId, locals.dri);
        output.disputed = 1;
        locals.log = QuotteryLoggerWithData{ 0, QUOTTERY_DISPUTED_EVENT_GROUP, id(0, 0, 0, input.eventGroupId), 0 };
        LOG_INFO(locals.log);
    }

    struct UserClaimReward_input
    {
        uint64 eventId;
    };
    struct UserClaimReward_output
    {
    };

    struct UserClaimReward_locals
    {
        id key;
        QtryOrder qo;
        uint64 winCondition;
        sint8 winOption;
        RewardTransfer_input rti;
        RewardTransfer_output rto;
    };

    // allow users to claim rewards before epoch ends
    PUBLIC_PROCEDURE_WITH_LOCALS(UserClaimReward)
    {
        if (qpi.invocationReward() != 1000000)
        {
            return; // no refund because of spam
        }
        // only allow claiming after the event is finalized (dispute window closed)
        if (!state.get().mEventFinalFlag.contains(input.eventId))
        {
            return; // no refund because of spam
        }
        state.get().mEventResult.get(input.eventId, locals.winOption);
        if (locals.winOption == QUOTTERY_RESULT_NOT_SET)
        {
            return; // no refund because of spam
        }

        locals.winCondition = posKey((uint64)(locals.winOption), input.eventId);
        locals.key = qpi.invocator();
        locals.key.u64._3 = locals.winCondition;
        if (state.get().mPositionInfo.contains(locals.key))
        {
            // return deposit
            if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
            // payout
            state.get().mPositionInfo.get(locals.key, locals.qo);
            locals.rti.amount = smul(state.get().wholeSharePrice, locals.qo.amount);
            locals.rti.eid = input.eventId;
            locals.rti.receiver = locals.qo.entity;
            locals.rti.needChargeFee = 1;
            CALL(RewardTransfer, locals.rti, locals.rto);
            if (!locals.rto.ok) return;
            // remove the position
            state.mut().mPositionInfo.removeByKey(locals.key);
        }
        state.mut().mPositionInfo.cleanupIfNeeded();
    }

    struct GOForceClaimReward_input
    {
        uint64 eventId;
        Array<id, 16> pubkeys;
    };
    struct GOForceClaimReward_output
    {
    };

    struct GOForceClaimReward_locals
    {
        sint32 i;
        id key;
        QtryOrder qo;
        uint64 winCondition, loseCondition;
        sint8 winOption;
        RewardTransfer_input rti;
        RewardTransfer_output rto;
    };

    PUBLIC_PROCEDURE_WITH_LOCALS(GOForceClaimReward)
    {
        if (qpi.invocator() != state.get().mQtryGov.mOperationId)
        {
            return;
        }
        // only allow claiming after the event is finalized (dispute window closed)
        if (!state.get().mEventFinalFlag.contains(input.eventId))
        {
            return;
        }
        state.get().mEventResult.get(input.eventId, locals.winOption);
        if (locals.winOption == QUOTTERY_RESULT_NOT_SET)
        {
            return;
        }

        locals.winCondition = posKey(locals.winOption, input.eventId);
        locals.loseCondition = posKey(1ULL - locals.winOption, input.eventId);

        for (locals.i = 0; locals.i < input.pubkeys.capacity(); locals.i++)
        {
            locals.key = input.pubkeys.get(locals.i);
            if (locals.key == NULL_ID) continue;
            locals.key.u64._3 = locals.winCondition;
            if (state.get().mPositionInfo.contains(locals.key))
            {
                // payout
                state.get().mPositionInfo.get(locals.key, locals.qo);
                locals.rti.amount = smul(state.get().wholeSharePrice, locals.qo.amount);
                locals.rti.eid = input.eventId;
                locals.rti.receiver = locals.qo.entity;
                locals.rti.needChargeFee = 1;
                CALL(RewardTransfer, locals.rti, locals.rto);
                if (!locals.rto.ok) return;
                // remove the position
                state.mut().mPositionInfo.removeByKey(locals.key);
            }

            locals.key.u64._3 = locals.loseCondition;
            if (state.get().mPositionInfo.contains(locals.key))
            {
                state.mut().mPositionInfo.removeByKey(locals.key);
            }
        }
        state.mut().mPositionInfo.cleanupIfNeeded();
    }

    struct FinalizeEvent_input
    {
        uint64 eventId;
        uint64 winOption;
    };
    struct FinalizeEvent_output
    {
    };

    struct FinalizeEvent_locals
    {
        sint64 index;
        id key, r;
        QtryOrder value;
        sint64 price;

        RewardTransfer_input rti;
        RewardTransfer_output rto;

        UpdatePosition_input upi;
        UpdatePosition_output upo;

        QuotteryLoggerWithData log;
    };

    PRIVATE_PROCEDURE_WITH_LOCALS(FinalizeEvent)
    {
        locals.log = QuotteryLoggerWithData{ 0, QUOTTERY_FINALIZE_EVENT, id(0,0,input.eventId,input.winOption), 0 };
        LOG_INFO(locals.log);
        state.mut().mEventFinalFlag.set(input.eventId, true);
        // cleaning all ABOrder
        locals.index = 0;

        // deleting ask 0
        locals.key = MakeOrderKey(input.eventId, 0, QUOTTERY_ASK_BIT, locals.r);
        locals.index = state.get().mABOrders.headIndex(locals.key);
        while (locals.index != NULL_INDEX)
        {
            locals.value = state.get().mABOrders.element(locals.index);
            {
                // return share
                locals.upi.uid = locals.value.entity;
                locals.upi.amountChange = locals.value.amount;
                locals.upi.oi.eid = input.eventId;
                locals.upi.oi.option = 0;
                locals.upi.oi.tradeBit = QUOTTERY_ASK_BIT;
                CALL(UpdatePosition, locals.upi, locals.upo);
            }
            state.mut().mABOrders.remove(locals.index);
            locals.index = state.get().mABOrders.headIndex(locals.key);
        }

        // deleting ask 1
        locals.key = MakeOrderKey(input.eventId, 1, QUOTTERY_ASK_BIT, locals.r);
        locals.index = state.get().mABOrders.headIndex(locals.key);
        while (locals.index != NULL_INDEX)
        {
            locals.value = state.get().mABOrders.element(locals.index);
            {
                // return share
                locals.upi.uid = locals.value.entity;
                locals.upi.amountChange = locals.value.amount;
                locals.upi.oi.eid = input.eventId;
                locals.upi.oi.option = 1;
                locals.upi.oi.tradeBit = QUOTTERY_ASK_BIT;
                CALL(UpdatePosition, locals.upi, locals.upo);
            }
            state.mut().mABOrders.remove(locals.index);
            locals.index = state.get().mABOrders.headIndex(locals.key);
        }

        // deleting bid 0
        locals.key = MakeOrderKey(input.eventId, 0, QUOTTERY_BID_BIT, locals.r);
        locals.index = state.get().mABOrders.headIndex(locals.key);
        while (locals.index != NULL_INDEX)
        {
            locals.value = state.get().mABOrders.element(locals.index);
            locals.price = state.get().mABOrders.priority(locals.index);
            // refund to users (continue on failure so remaining orders aren't stuck)
            locals.rti.receiver = locals.value.entity;
            locals.rti.amount = smul(locals.value.amount, locals.price);
            locals.rti.eid = input.eventId;
            locals.rti.needChargeFee = 0;
            CALL(RewardTransfer, locals.rti, locals.rto);

            state.mut().mABOrders.remove(locals.index);
            locals.index = state.get().mABOrders.headIndex(locals.key);
        }

        // deleting bid 1
        locals.key = MakeOrderKey(input.eventId, 1, QUOTTERY_BID_BIT, locals.r);
        locals.index = state.get().mABOrders.headIndex(locals.key);
        while (locals.index != NULL_INDEX)
        {
            locals.value = state.get().mABOrders.element(locals.index);
            locals.price = state.get().mABOrders.priority(locals.index);
            // refund to users (continue on failure so remaining orders aren't stuck)
            locals.rti.receiver = locals.value.entity;
            locals.rti.amount = smul(locals.value.amount, locals.price);
            locals.rti.eid = input.eventId;
            locals.rti.needChargeFee = 0;
            CALL(RewardTransfer, locals.rti, locals.rto);

            state.mut().mABOrders.remove(locals.index);
            locals.index = state.get().mABOrders.headIndex(locals.key);
        }

        state.mut().mABOrders.cleanupIfNeeded();
    }
public:
    struct ResolveDispute_input
    {
        uint64 eventId;
        sint64 vote;
    };
    struct ResolveDispute_output
    {
    };

    struct ResolveDispute_locals
    {
        sint32 i;
        sint8 result;
        sint32 voteCount; // final vote count for result
        sint32 isComputor;
        DisputeResolveInfo dri;
        sint32 voteNo, voteYes;

        sint64 disputeRewardPot;
        sint64 rewardPerComputor;
        sint64 rewardForWinner;
        id winnerId;
        sint8 GOResult;

        FinalizeEvent_input fei;
        FinalizeEvent_output feo;

        DepositInfo diDisputer;
        DepositInfo diGO;
        id pubkey;
        QtryMarketGroupLink marketGroupLink;
        QtryEventGroupInfo eventGroupInfo;

        QuotteryLoggerWithData log;
    };
    // resolve a disputed event, can only be called by computors
    PUBLIC_PROCEDURE_WITH_LOCALS(ResolveDispute)
    {
        if (qpi.invocationReward() < 10000000)
        {
            return;
        }
        locals.isComputor = -1;
        for (locals.i = 0; locals.i < NUMBER_OF_COMPUTORS; locals.i++)
        {
            if (qpi.computor(locals.i) == qpi.invocator())
            {
                locals.isComputor = locals.i;
                break;
            }
        }
        if (locals.isComputor == -1)
        {
            return;
        }
        // if this is called by computor, return deposit
        qpi.transfer(qpi.invocator(), qpi.invocationReward());
        if (!state.get().mDisputeInfo.contains(input.eventId))
        {
            return;
        }

        if (input.vote != 0 && input.vote != 1) // invalid vote
        {
            return;
        }

        state.get().mDisputeResolver.get(input.eventId, locals.dri);
        locals.dri.epochData.set(locals.isComputor, qpi.epoch());
        locals.dri.voteData.set(locals.isComputor, (sint8)(input.vote));
        state.mut().mDisputeResolver.set(input.eventId, locals.dri);

        locals.log = QuotteryLoggerWithData{ 0, QUOTTERY_RESOLVE_DISPUTE, id(0,input.eventId, locals.isComputor, input.vote), 0 };
        LOG_INFO(locals.log);

        locals.voteNo = 0;
        locals.voteYes = 0;
        for (locals.i = 0; locals.i < NUMBER_OF_COMPUTORS; locals.i++)
        {
            if (locals.dri.epochData.get(locals.i) == qpi.epoch())
            {
                if (locals.dri.voteData.get(locals.i) == 0) locals.voteNo++;
                else locals.voteYes++;
            }
        }
        locals.result = QUOTTERY_RESULT_NOT_SET;
        if (locals.voteNo >= QUORUM)
        {
            locals.result = QUOTTERY_RESULT_NO;
            locals.voteCount = locals.voteNo;
        }
        if (locals.voteYes >= QUORUM)
        {
            locals.result = QUOTTERY_RESULT_YES;
            locals.voteCount = locals.voteYes;
        }

        if (locals.result == QUOTTERY_RESULT_NOT_SET)
        {
            return;
        }

        // POT have: mDepositAmountForDispute x 2: from disputer and GO
        // computors takes 0.3 x POT
        // disputer takes 0.7 x POT
        state.get().mDisputeInfo.get(input.eventId, locals.diDisputer);
        state.get().mGODepositInfo.get(input.eventId, locals.diGO);
        locals.disputeRewardPot = locals.diDisputer.amount + locals.diGO.amount;

        locals.rewardPerComputor = QPI::div(QPI::div(locals.disputeRewardPot * 3LL, 10LL), sint64(locals.voteCount));

        locals.rewardForWinner = locals.disputeRewardPot - locals.rewardPerComputor * sint64(locals.voteCount);
        state.get().mEventResult.get(input.eventId, locals.GOResult);
        if (locals.GOResult == locals.result)
        {
            locals.winnerId = locals.diGO.pubkey;
        }
        else
        {
            locals.winnerId = locals.diDisputer.pubkey;
        }

        qpi.transfer(locals.winnerId, locals.rewardForWinner);

        for (locals.i = 0; locals.i < NUMBER_OF_COMPUTORS; locals.i++)
        {
            if (locals.dri.epochData.get(locals.i) == qpi.epoch())
            {
                if (locals.dri.voteData.get(locals.i) == locals.result)
                {
                    locals.pubkey = qpi.computor(locals.i);
                    qpi.transfer(locals.pubkey, locals.rewardPerComputor);
                }
            }
        }

        // clean array
        state.mut().mDisputeInfo.removeByKey(input.eventId);
        state.mut().mGODepositInfo.removeByKey(input.eventId);
        state.mut().mDisputeResolver.removeByKey(input.eventId);

        // finalize the event (guard against double-finalization)
        if (!state.get().mEventFinalFlag.contains(input.eventId))
        {
            locals.fei.eventId = input.eventId;
            locals.fei.winOption = locals.result;
            state.mut().mEventResult.set(input.eventId, locals.result);
            CALL(FinalizeEvent, locals.fei, locals.feo);
            if (state.get().mMarketGroupLink.get(input.eventId, locals.marketGroupLink) &&
                state.get().mEventGroupInfo.get(locals.marketGroupLink.eventGroupId, locals.eventGroupInfo))
            {
                locals.eventGroupInfo.finalizedMarketCount++;
                if (locals.eventGroupInfo.finalizedMarketCount == locals.eventGroupInfo.marketCount)
                {
                    locals.eventGroupInfo.status = QUOTTERY_EVENT_GROUP_STATUS_FINALIZED;
                    locals.log = QuotteryLoggerWithData{
                        0,
                        QUOTTERY_FINALIZED_EVENT_GROUP,
                        id(0, 0, 0, locals.marketGroupLink.eventGroupId),
                        0
                    };
                    LOG_INFO(locals.log);
                }
                state.mut().mEventGroupInfo.set(locals.marketGroupLink.eventGroupId, locals.eventGroupInfo);
            }
        }
    }

    struct ResolveEventDispute_input
    {
        uint64 eventGroupId;
        uint64 winningMarketId;
    };
    struct ResolveEventDispute_output
    {
        bit resolved;
    };
    struct ResolveEventDispute_locals
    {
        sint32 i;
        sint32 isComputor;
        sint32 voteCount;
        sint64 disputeRewardPot;
        sint64 rewardPerComputor;
        sint64 rewardForWinner;
        sint8 resultIndex;
        sint8 goResultIndex;
        id winnerId;
        id pubkey;
        QtryEventGroupInfo eventGroupInfo;
        QtryEventGroupMarkets markets;
        QtryMarketGroupLink winningMarketLink;
        DisputeResolveInfo dri;
        DepositInfo diDisputer;
        DepositInfo diGO;
        QuotteryLoggerWithData log;
    };

    PUBLIC_PROCEDURE_WITH_LOCALS(ResolveEventDispute)
    {
        if (qpi.invocationReward() < 10000000)
        {
            return;
        }
        locals.isComputor = -1;
        for (locals.i = 0; locals.i < NUMBER_OF_COMPUTORS; locals.i++)
        {
            if (qpi.computor(locals.i) == qpi.invocator())
            {
                locals.isComputor = locals.i;
                break;
            }
        }
        if (locals.isComputor == -1)
        {
            return;
        }
        qpi.transfer(qpi.invocator(), qpi.invocationReward());

        if (!state.get().mEventGroupDisputeInfo.contains(input.eventGroupId) ||
            !state.get().mEventGroupInfo.get(input.eventGroupId, locals.eventGroupInfo) ||
            locals.eventGroupInfo.mode != QUOTTERY_EVENT_GROUP_MODE_EXCLUSIVE_ONE ||
            !state.get().mEventGroupMarkets.get(input.eventGroupId, locals.markets) ||
            !state.get().mMarketGroupLink.get(input.winningMarketId, locals.winningMarketLink) ||
            locals.winningMarketLink.eventGroupId != input.eventGroupId)
        {
            return;
        }

        state.get().mEventGroupDisputeResolver.get(input.eventGroupId, locals.dri);
        locals.resultIndex = (sint8)locals.winningMarketLink.marketIndex;
        locals.dri.epochData.set(locals.isComputor, qpi.epoch());
        locals.dri.voteData.set(locals.isComputor, locals.resultIndex);
        state.mut().mEventGroupDisputeResolver.set(input.eventGroupId, locals.dri);

        locals.voteCount = 0;
        for (locals.i = 0; locals.i < NUMBER_OF_COMPUTORS; locals.i++)
        {
            if (locals.dri.epochData.get(locals.i) == qpi.epoch() &&
                locals.dri.voteData.get(locals.i) == locals.resultIndex)
            {
                locals.voteCount++;
            }
        }
        if (locals.voteCount < QUORUM)
        {
            return;
        }

        state.get().mEventGroupDisputeInfo.get(input.eventGroupId, locals.diDisputer);
        state.get().mEventGroupGODepositInfo.get(input.eventGroupId, locals.diGO);
        locals.disputeRewardPot = locals.diDisputer.amount + locals.diGO.amount;
        locals.rewardPerComputor = QPI::div(
            QPI::div(locals.disputeRewardPot * 3LL, 10LL),
            sint64(locals.voteCount)
        );
        locals.rewardForWinner = locals.disputeRewardPot - locals.rewardPerComputor * sint64(locals.voteCount);
        state.get().mEventGroupResult.get(input.eventGroupId, locals.goResultIndex);
        if (locals.goResultIndex == locals.resultIndex)
        {
            locals.winnerId = locals.diGO.pubkey;
        }
        else
        {
            locals.winnerId = locals.diDisputer.pubkey;
        }
        qpi.transfer(locals.winnerId, locals.rewardForWinner);

        for (locals.i = 0; locals.i < NUMBER_OF_COMPUTORS; locals.i++)
        {
            if (locals.dri.epochData.get(locals.i) == qpi.epoch() &&
                locals.dri.voteData.get(locals.i) == locals.resultIndex)
            {
                locals.pubkey = qpi.computor(locals.i);
                qpi.transfer(locals.pubkey, locals.rewardPerComputor);
            }
        }

        state.mut().mEventGroupResult.set(input.eventGroupId, locals.resultIndex);
        for (locals.i = 0; locals.i < locals.eventGroupInfo.marketCount; locals.i++)
        {
            if (locals.i == locals.winningMarketLink.marketIndex)
            {
                state.mut().mEventResult.set(locals.markets.marketIds.get(locals.i), QUOTTERY_RESULT_YES);
            }
            else
            {
                state.mut().mEventResult.set(locals.markets.marketIds.get(locals.i), QUOTTERY_RESULT_NO);
            }
        }
        state.mut().mEventGroupDisputeInfo.removeByKey(input.eventGroupId);
        state.mut().mEventGroupGODepositInfo.removeByKey(input.eventGroupId);
        state.mut().mEventGroupDisputeResolver.removeByKey(input.eventGroupId);
        state.mut().mEventGroupDisputeResolved.set(input.eventGroupId, 1);

        output.resolved = 1;
        locals.log = QuotteryLoggerWithData{
            0,
            QUOTTERY_RESOLVED_EVENT_GROUP_DISPUTE,
            id(0, locals.winningMarketLink.marketIndex, input.eventGroupId, input.winningMarketId),
            0
        };
        LOG_INFO(locals.log);
    }

    /**
    * Try to finalize an event
    * call by GO - at least 24 hours after end date
    * the reward distribution goes thru if there is no dispute
    * @param eventId
    */
    struct TryFinalizeEvent_input
    {
        uint64 eventId;
    };
    struct TryFinalizeEvent_output
    {
    };

    struct TryFinalizeEvent_locals
    {
        uint64 winOption;
        sint8 result;
        DepositInfo di;
        QtryEventInfo qei;
        QtryMarketGroupLink marketGroupLink;
        QtryEventGroupInfo eventGroupInfo;
        QuotteryLogger log;
        QuotteryLoggerWithData groupLog;
        uint32 publishResultTick;

        FinalizeEvent_input fei;
        FinalizeEvent_output feo;
    };

    PUBLIC_PROCEDURE_WITH_LOCALS(TryFinalizeEvent)
    {
        if (qpi.invocator() != state.get().mQtryGov.mOperationId)
        {
            return;
        }
        if (!state.get().mEventInfo.get(input.eventId, locals.qei))
        {
            return;
        }
        if (state.get().mEventFinalFlag.contains(input.eventId))
        {
            return;
        }

        if (state.get().mMarketGroupLink.get(input.eventId, locals.marketGroupLink) &&
            state.get().mEventGroupInfo.get(locals.marketGroupLink.eventGroupId, locals.eventGroupInfo) &&
            locals.eventGroupInfo.mode == QUOTTERY_EVENT_GROUP_MODE_EXCLUSIVE_ONE)
        {
            if (state.get().mEventGroupDisputeInfo.contains(locals.marketGroupLink.eventGroupId) ||
                !state.get().mEventGroupResult.get(locals.marketGroupLink.eventGroupId, locals.result))
            {
                return;
            }
            state.get().mEventGroupResultPublishTickTime.get(
                locals.marketGroupLink.eventGroupId,
                locals.publishResultTick
            );
            if (!state.get().mEventGroupDisputeResolved.contains(locals.marketGroupLink.eventGroupId) &&
                locals.publishResultTick + QUOTTERY_DISPUTE_WINDOW > qpi.tick())
            {
                return;
            }

            state.get().mEventResult.get(input.eventId, locals.result);
            if (locals.result == QUOTTERY_RESULT_NOT_SET)
            {
                return;
            }
            locals.winOption = (uint64)locals.result;

            if (state.get().mEventGroupGODepositInfo.get(locals.marketGroupLink.eventGroupId, locals.di))
            {
                qpi.transfer(locals.di.pubkey, locals.di.amount);
                state.mut().mEventGroupGODepositInfo.removeByKey(locals.marketGroupLink.eventGroupId);
            }

            locals.fei.eventId = input.eventId;
            locals.fei.winOption = locals.winOption;
            CALL(FinalizeEvent, locals.fei, locals.feo);

            locals.eventGroupInfo.finalizedMarketCount++;
            if (locals.eventGroupInfo.finalizedMarketCount == locals.eventGroupInfo.marketCount)
            {
                locals.eventGroupInfo.status = QUOTTERY_EVENT_GROUP_STATUS_FINALIZED;
                locals.groupLog = QuotteryLoggerWithData{
                    0,
                    QUOTTERY_FINALIZED_EVENT_GROUP,
                    id(0, 0, 0, locals.marketGroupLink.eventGroupId),
                    0
                };
                LOG_INFO(locals.groupLog);
            }
            state.mut().mEventGroupInfo.set(locals.marketGroupLink.eventGroupId, locals.eventGroupInfo);
            return;
        }

        if (state.get().mDisputeInfo.contains(input.eventId))
        {
            // this event is being disputed: users not agree with result from operation team
            return;
        }
        // only finalizing after 1000 ticks since result is published
        state.get().mEventResultPublishTickTime.get(input.eventId, locals.publishResultTick);
        if (locals.publishResultTick + QUOTTERY_DISPUTE_WINDOW > qpi.tick())
        {
            return;
        }

        state.get().mEventResult.get(input.eventId, locals.result);
        if (locals.result == QUOTTERY_RESULT_NOT_SET)
        {
            return;
        }
        if (locals.result == QUOTTERY_RESULT_NO)
        {
            locals.winOption = 0;
        }
        else
        {
            locals.winOption = 1;
        }

        // ALL passed, no dispute, return the deposit to GO
        state.get().mGODepositInfo.get(input.eventId, locals.di);
        qpi.transfer(locals.di.pubkey, locals.di.amount);
        state.mut().mGODepositInfo.removeByKey(input.eventId); // clean up

        locals.fei.eventId = input.eventId;
        locals.fei.winOption = locals.winOption;
        CALL(FinalizeEvent, locals.fei, locals.feo);

        if (state.get().mMarketGroupLink.get(input.eventId, locals.marketGroupLink) &&
            state.get().mEventGroupInfo.get(locals.marketGroupLink.eventGroupId, locals.eventGroupInfo))
        {
            locals.eventGroupInfo.finalizedMarketCount++;
            if (locals.eventGroupInfo.finalizedMarketCount == locals.eventGroupInfo.marketCount)
            {
                locals.eventGroupInfo.status = QUOTTERY_EVENT_GROUP_STATUS_FINALIZED;
                locals.groupLog = QuotteryLoggerWithData{
                    0,
                    QUOTTERY_FINALIZED_EVENT_GROUP,
                    id(0, 0, 0, locals.marketGroupLink.eventGroupId),
                    0
                };
                LOG_INFO(locals.groupLog);
            }
            state.mut().mEventGroupInfo.set(locals.marketGroupLink.eventGroupId, locals.eventGroupInfo);
        }
    }

    /**************************************/
    /************VIEW FUNCTIONS************/
    /**************************************/
    /**
     */
    PUBLIC_FUNCTION(BasicInfo)
    {
        setMemory(output, 0);
        output.operationFee = state.get().mQtryGov.mOperationFee;
        output.gameOperator = state.get().mQtryGov.mOperationId;
        output.shareholderFee = state.get().mQtryGov.mShareHolderFee;
        output.burnFee = state.get().mQtryGov.mBurnFee;
        output.shareholdersRevenue = state.get().mShareholdersRevenue;
        output.operationRevenue = state.get().mOperationRevenue;
        output.nIssuedEvent = state.get().mCurrentEventID;
        output.burnedAmount = state.get().mBurnedAmount;
        output.mFeePerDay = state.get().mQtryGov.mFeePerDay;
        output.antiSpamAmount = state.get().mOperationParams.mAntiSpamAmount;
        output.depositAmountForDispute = state.get().mQtryGov.mDepositAmountForDispute;
        output.nIssuedEventGroup = state.get().mCurrentEventGroupID;
    }

    struct GetActiveEvent_input
    {
    };
    struct GetActiveEvent_output
    {
        Array<uint64, QUOTTERY_MAX_CONCURRENT_EVENT> recentActiveEvent;
    };

    struct GetActiveEvent_locals
    {
        sint64 i;
    };
    /**
     * @return a list of active eventID.
     */
    PUBLIC_FUNCTION_WITH_LOCALS(GetActiveEvent)
    {
        copyMemory(output.recentActiveEvent, state.get().mRecentActiveEvent);
    }

    struct GetUserPosition_input
    {
        id uid;
    };

    struct GetUserPosition_output
    {
        struct PositionInfo
        {
            uint64 eo; //packed eventId and option bit
            sint64 amount;
        };
        sint64 count;
        Array<PositionInfo, 1024> p;
    };

    struct GetUserPosition_locals
    {
        uint64 k, e;
        id key;
        QtryOrder qo;
        sint64 i;
        GetUserPosition_output::PositionInfo pi;
    };
    /**
     * @brief PUBLIC VIEW FUNCTION
     * Returns all positions of an ID
     */
    PUBLIC_FUNCTION_WITH_LOCALS(GetUserPosition)
    {
        setMemory(output, 0);
        output.count = 0;
        for (locals.i = 0; locals.i < QUOTTERY_MAX_CONCURRENT_EVENT; locals.i++)
        {
            if (output.count == output.p.capacity()) break;
            locals.e = state.get().mRecentActiveEvent.get(locals.i);
            locals.key = MakePosKey(input.uid, locals.e, 0);
            if (state.get().mPositionInfo.get(locals.key, locals.qo))
            {
                locals.pi.amount = locals.qo.amount;
                locals.pi.eo = posKey(0, locals.e);
                output.p.set(output.count++, locals.pi);
            }

            locals.key = MakePosKey(input.uid, locals.e, 1);
            if (state.get().mPositionInfo.get(locals.key, locals.qo))
            {
                locals.pi.amount = locals.qo.amount;
                locals.pi.eo = posKey(1, locals.e);
                output.p.set(output.count++, locals.pi);
            }
        }
    }

    /**************************************/
    /************CORE FUNCTIONS************/
    /**************************************/
    /**
    * Create a event
    * if the provided info is failed to create a event, fund will be returned to invocator.
    * @param eventDesc (32 bytes): event description 32 bytes
    * @param optionDesc (256 bytes): option descriptions, 32 bytes for each option from 0 to 7, leave empty(zeroes) for unused memory space
    * @param closeDate (4 bytes): date in quotteryData format, thefirst byte is year, the second byte is month, the third byte is day(in month), the fourth byte is 0.
    * @param endDate (4 bytes): date in quotteryData format, thefirst byte is year, the second byte is month, the third byte is day(in month), the fourth byte is 0.
    */
    struct CreateEvent_input
    {
        QtryEventInfo qei;
    };
    struct CreateEvent_output
    {
    };
    struct CreateEvent_locals
    {
        DateAndTime dtNow;
        uint64 duration;
        sint64 fee;

        QtryEventInfo qei;
        QuotteryLogger log;
        sint32 i;
        DisputeResolveInfo dri;
    };

    PUBLIC_PROCEDURE_WITH_LOCALS(CreateEvent)
    {
        // only allow GO (game operator) to create event
        if (qpi.invocator() != state.get().mQtryGov.mOperationId)
        {
            if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
            return;
        }

        locals.dtNow = qpi.now();
        if (input.qei.endDate < locals.dtNow)
        {
            locals.log = QuotteryLogger{ 0, QUOTTERY_INVALID_DATETIME ,0 };
            LOG_INFO(locals.log);
            if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
            return;
        }

        locals.duration = input.qei.endDate.durationMicrosec(locals.dtNow);
        locals.duration = divUp(locals.duration, 86400000000ULL); // 86400000000 us per day

        locals.fee = locals.duration * state.get().mQtryGov.mFeePerDay;


        // fee is higher than sent amount, exit
        if (locals.fee > qpi.invocationReward())
        {
            locals.log = QuotteryLogger{ 0, QUOTTERY_INSUFFICIENT_FUND ,0 };
            LOG_INFO(locals.log);
            if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
            return;
        }
        if (state.get().mEventInfo.population() == QUOTTERY_MAX_CONCURRENT_EVENT)
        {
            // out of storage
            if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
            return;
        }

        locals.qei = input.qei;
        locals.qei.eid = state.mut().mCurrentEventID++;
        locals.qei.openDate = locals.dtNow;

        state.mut().mEventInfo.set(locals.qei.eid, locals.qei);
        state.mut().mEventResult.set(locals.qei.eid, QUOTTERY_RESULT_NOT_SET);
        state.mut().mEventResultPublishTickTime.set(locals.qei.eid, 0);
        state.mut().mDisputeInfo.removeByKey(locals.qei.eid); // clean if any

        if (qpi.invocationReward() > locals.fee)
        {
            qpi.transfer(qpi.invocator(), qpi.invocationReward() - locals.fee);
        }
        state.mut().mRecentActiveEvent.set(mod(locals.qei.eid, QUOTTERY_MAX_CONCURRENT_EVENT), locals.qei.eid);

        for (locals.i = 0; locals.i < NUMBER_OF_COMPUTORS; locals.i++)
        {
            locals.dri.epochData.set(locals.i, 10000);
            locals.dri.voteData.set(locals.i, QUOTTERY_RESULT_NOT_SET);
        }
        state.mut().mDisputeResolver.set(locals.qei.eid, locals.dri);

        locals.log = QuotteryLogger{ 0, QUOTTERY_CREATED_EVENT ,0 };
        LOG_INFO(locals.log);
    }

    struct CreateEventGroup_input
    {
        Array<id, 4> desc;
        uint16 expectedMarketCount;
        uint8 mode;
    };
    struct CreateEventGroup_output
    {
        uint64 eventGroupId;
        bit created;
    };
    struct CreateEventGroup_locals
    {
        QtryEventGroupInfo eventGroupInfo;
        QtryEventGroupMarkets markets;
        QuotteryLoggerWithData log;
    };

    PUBLIC_PROCEDURE_WITH_LOCALS(CreateEventGroup)
    {
        if (qpi.invocator() != state.get().mQtryGov.mOperationId)
        {
            if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
            return;
        }
        if (input.mode > QUOTTERY_EVENT_GROUP_MODE_EXCLUSIVE_ONE ||
            input.expectedMarketCount == 0 ||
            input.expectedMarketCount > QUOTTERY_MAX_MARKETS_PER_EVENT_GROUP ||
            (input.mode == QUOTTERY_EVENT_GROUP_MODE_EXCLUSIVE_ONE && input.expectedMarketCount < 2))
        {
            if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
            return;
        }
        if (state.get().mEventGroupInfo.population() == QUOTTERY_MAX_CONCURRENT_EVENT)
        {
            if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
            return;
        }

        setMemory(locals.eventGroupInfo, 0);
        setMemory(locals.markets, 0);
        locals.eventGroupInfo.eventGroupId = state.mut().mCurrentEventGroupID++;
        locals.eventGroupInfo.createdDate = qpi.now();
        locals.eventGroupInfo.desc = input.desc;
        locals.eventGroupInfo.expectedMarketCount = input.expectedMarketCount;
        locals.eventGroupInfo.marketCount = 0;
        locals.eventGroupInfo.mode = input.mode;
        locals.eventGroupInfo.status = QUOTTERY_EVENT_GROUP_STATUS_DRAFT;

        state.mut().mEventGroupInfo.set(locals.eventGroupInfo.eventGroupId, locals.eventGroupInfo);
        state.mut().mEventGroupMarkets.set(locals.eventGroupInfo.eventGroupId, locals.markets);

        output.eventGroupId = locals.eventGroupInfo.eventGroupId;
        output.created = 1;
        locals.log = QuotteryLoggerWithData{
            0,
            QUOTTERY_CREATED_EVENT_GROUP,
            id(0, input.mode, input.expectedMarketCount, locals.eventGroupInfo.eventGroupId),
            0
        };
        LOG_INFO(locals.log);

        if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
    }

    struct AddMarket_input
    {
        uint64 eventGroupId;
        QtryEventInfo qei;
    };
    struct AddMarket_output
    {
        uint64 marketId;
        bit created;
    };
    struct AddMarket_locals
    {
        DateAndTime dtNow;
        uint64 duration;
        sint64 fee;
        sint32 i;
        QtryEventInfo qei;
        QtryEventGroupInfo eventGroupInfo;
        QtryEventGroupMarkets markets;
        QtryMarketGroupLink marketGroupLink;
        DisputeResolveInfo dri;
        QuotteryLogger legacyLog;
        QuotteryLoggerWithData log;
    };

    PUBLIC_PROCEDURE_WITH_LOCALS(AddMarket)
    {
        if (qpi.invocator() != state.get().mQtryGov.mOperationId)
        {
            if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
            return;
        }
        if (!state.get().mEventGroupInfo.get(input.eventGroupId, locals.eventGroupInfo) ||
            locals.eventGroupInfo.status != QUOTTERY_EVENT_GROUP_STATUS_DRAFT ||
            locals.eventGroupInfo.marketCount >= locals.eventGroupInfo.expectedMarketCount)
        {
            if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
            return;
        }

        locals.dtNow = qpi.now();
        if (input.qei.endDate < locals.dtNow)
        {
            if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
            return;
        }
        locals.duration = input.qei.endDate.durationMicrosec(locals.dtNow);
        locals.duration = divUp(locals.duration, 86400000000ULL);
        locals.fee = locals.duration * state.get().mQtryGov.mFeePerDay;
        if (locals.fee > qpi.invocationReward() ||
            state.get().mEventInfo.population() == QUOTTERY_MAX_CONCURRENT_EVENT)
        {
            if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
            return;
        }

        locals.qei = input.qei;
        locals.qei.eid = state.mut().mCurrentEventID++;
        locals.qei.openDate = locals.dtNow;
        state.mut().mEventInfo.set(locals.qei.eid, locals.qei);
        state.mut().mEventResult.set(locals.qei.eid, QUOTTERY_RESULT_NOT_SET);
        state.mut().mEventResultPublishTickTime.set(locals.qei.eid, 0);
        state.mut().mDisputeInfo.removeByKey(locals.qei.eid);

        for (locals.i = 0; locals.i < NUMBER_OF_COMPUTORS; locals.i++)
        {
            locals.dri.epochData.set(locals.i, 10000);
            locals.dri.voteData.set(locals.i, QUOTTERY_RESULT_NOT_SET);
        }
        state.mut().mDisputeResolver.set(locals.qei.eid, locals.dri);

        state.get().mEventGroupMarkets.get(input.eventGroupId, locals.markets);
        locals.markets.marketIds.set(locals.eventGroupInfo.marketCount, locals.qei.eid);
        state.mut().mEventGroupMarkets.set(input.eventGroupId, locals.markets);

        locals.marketGroupLink.eventGroupId = input.eventGroupId;
        locals.marketGroupLink.marketIndex = locals.eventGroupInfo.marketCount;
        state.mut().mMarketGroupLink.set(locals.qei.eid, locals.marketGroupLink);

        locals.eventGroupInfo.marketCount++;
        state.mut().mEventGroupInfo.set(input.eventGroupId, locals.eventGroupInfo);

        output.marketId = locals.qei.eid;
        output.created = 1;
        locals.legacyLog = QuotteryLogger{ 0, QUOTTERY_CREATED_EVENT, 0 };
        LOG_INFO(locals.legacyLog);
        locals.log = QuotteryLoggerWithData{
            0,
            QUOTTERY_ADDED_MARKET_TO_EVENT_GROUP,
            id(0, locals.marketGroupLink.marketIndex, input.eventGroupId, locals.qei.eid),
            0
        };
        LOG_INFO(locals.log);

        if (qpi.invocationReward() > locals.fee)
        {
            qpi.transfer(qpi.invocator(), qpi.invocationReward() - locals.fee);
        }
    }

    struct OpenEvent_input
    {
        uint64 eventGroupId;
    };
    struct OpenEvent_output
    {
        bit opened;
    };
    struct OpenEvent_locals
    {
        uint16 i;
        QtryEventGroupInfo eventGroupInfo;
        QtryEventGroupMarkets markets;
        QtryEventInfo qei;
        QuotteryLoggerWithData log;
    };

    PUBLIC_PROCEDURE_WITH_LOCALS(OpenEvent)
    {
        if (qpi.invocator() != state.get().mQtryGov.mOperationId)
        {
            if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
            return;
        }
        if (!state.get().mEventGroupInfo.get(input.eventGroupId, locals.eventGroupInfo) ||
            locals.eventGroupInfo.status != QUOTTERY_EVENT_GROUP_STATUS_DRAFT ||
            locals.eventGroupInfo.marketCount != locals.eventGroupInfo.expectedMarketCount)
        {
            if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
            return;
        }
        if (!state.get().mEventGroupMarkets.get(input.eventGroupId, locals.markets))
        {
            if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
            return;
        }

        for (locals.i = 0; locals.i < locals.eventGroupInfo.marketCount; locals.i++)
        {
            if (!state.get().mEventInfo.get(locals.markets.marketIds.get(locals.i), locals.qei) ||
                locals.qei.endDate < qpi.now())
            {
                if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
                return;
            }
        }

        locals.eventGroupInfo.status = QUOTTERY_EVENT_GROUP_STATUS_OPEN;
        locals.eventGroupInfo.openedDate = qpi.now();
        state.mut().mEventGroupInfo.set(input.eventGroupId, locals.eventGroupInfo);
        for (locals.i = 0; locals.i < locals.eventGroupInfo.marketCount; locals.i++)
        {
            state.get().mEventInfo.get(locals.markets.marketIds.get(locals.i), locals.qei);
            locals.qei.openDate = locals.eventGroupInfo.openedDate;
            state.mut().mEventInfo.set(locals.qei.eid, locals.qei);
            state.mut().mRecentActiveEvent.set(
                mod(locals.qei.eid, QUOTTERY_MAX_CONCURRENT_EVENT),
                locals.qei.eid
            );
        }

        output.opened = 1;
        locals.log = QuotteryLoggerWithData{
            0,
            QUOTTERY_OPENED_EVENT_GROUP,
            id(0, locals.eventGroupInfo.mode, locals.eventGroupInfo.marketCount, input.eventGroupId),
            0
        };
        LOG_INFO(locals.log);
        if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
    }

    struct CancelEventGroup_input
    {
        uint64 eventGroupId;
    };
    struct CancelEventGroup_output
    {
        bit canceled;
    };
    struct CancelEventGroup_locals
    {
        uint16 i;
        uint64 marketId;
        QtryEventGroupInfo eventGroupInfo;
        QtryEventGroupMarkets markets;
        QuotteryLoggerWithData log;
    };

    PUBLIC_PROCEDURE_WITH_LOCALS(CancelEventGroup)
    {
        if (qpi.invocator() != state.get().mQtryGov.mOperationId)
        {
            if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
            return;
        }
        if (!state.get().mEventGroupInfo.get(input.eventGroupId, locals.eventGroupInfo) ||
            locals.eventGroupInfo.status != QUOTTERY_EVENT_GROUP_STATUS_DRAFT ||
            !state.get().mEventGroupMarkets.get(input.eventGroupId, locals.markets))
        {
            if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
            return;
        }

        for (locals.i = 0; locals.i < locals.eventGroupInfo.marketCount; locals.i++)
        {
            locals.marketId = locals.markets.marketIds.get(locals.i);
            state.mut().mEventResult.removeByKey(locals.marketId);
            state.mut().mEventResultPublishTickTime.removeByKey(locals.marketId);
            state.mut().mDisputeInfo.removeByKey(locals.marketId);
            state.mut().mGODepositInfo.removeByKey(locals.marketId);
            state.mut().mDisputeResolver.removeByKey(locals.marketId);
            state.mut().mEventInfo.removeByKey(locals.marketId);
            state.mut().mMarketGroupLink.removeByKey(locals.marketId);
        }
        state.mut().mEventGroupMarkets.removeByKey(input.eventGroupId);
        state.mut().mEventGroupInfo.removeByKey(input.eventGroupId);
        output.canceled = 1;
        locals.log = QuotteryLoggerWithData{
            0,
            QUOTTERY_CANCELED_EVENT_GROUP,
            id(0, 0, locals.eventGroupInfo.marketCount, input.eventGroupId),
            0
        };
        LOG_INFO(locals.log);
        if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
    }

    struct ConvertNegRiskPositions_input
    {
        uint64 eventGroupId;
        uint64 noMarketMask;
        sint64 amount;
    };
    struct ConvertNegRiskPositions_output
    {
        bit converted;
        sint64 collateralOut;
    };
    struct ConvertNegRiskPositions_locals
    {
        uint16 i;
        uint16 noPositionCount;
        uint64 validMarketMask;
        uint64 removedPositionCount;
        uint64 newPositionCount;
        uint64 resultingPopulation;
        uint64 marketId;
        sint64 collateralPerSet;
        id positionKey;
        QtryOrder position;
        QtryEventGroupInfo eventGroupInfo;
        QtryEventGroupMarkets markets;
        QuotteryNegRiskConversionLogger log;
    };

    /**
     * @brief Converts NO positions in an EXCLUSIVE_ONE event group into the
     * economically equivalent collateral and complementary YES positions.
     * For m selected NO positions, the output is (m - 1) complete sets of
     * collateral plus one YES position in every unselected market.
     */
    PUBLIC_PROCEDURE_WITH_LOCALS(ConvertNegRiskPositions)
    {
        output.converted = 0;
        output.collateralOut = 0;

        if (state.get().mOperationParams.mAntiSpamAmount)
        {
            if (qpi.invocationReward() < state.get().mOperationParams.mAntiSpamAmount) return;
            if (qpi.invocationReward() > state.get().mOperationParams.mAntiSpamAmount)
            {
                qpi.transfer(qpi.invocator(), qpi.invocationReward() - state.get().mOperationParams.mAntiSpamAmount);
            }
        }

        if (input.amount <= 0 || input.amount >= (sint64)QUOTTERY_MAX_AMOUNT || input.noMarketMask == 0)
        {
            return;
        }
        if (!state.get().mEventGroupInfo.get(input.eventGroupId, locals.eventGroupInfo) ||
            locals.eventGroupInfo.mode != QUOTTERY_EVENT_GROUP_MODE_EXCLUSIVE_ONE ||
            locals.eventGroupInfo.status != QUOTTERY_EVENT_GROUP_STATUS_OPEN ||
            locals.eventGroupInfo.marketCount < 2 ||
            state.get().mEventGroupResult.contains(input.eventGroupId) ||
            !state.get().mEventGroupMarkets.get(input.eventGroupId, locals.markets))
        {
            return;
        }

        if (locals.eventGroupInfo.marketCount < QUOTTERY_MAX_MARKETS_PER_EVENT_GROUP)
        {
            locals.validMarketMask = (1ULL << locals.eventGroupInfo.marketCount) - 1;
            if (input.noMarketMask & ~locals.validMarketMask)
            {
                return;
            }
        }

        // Validate every input position and preflight every output position.
        for (locals.i = 0; locals.i < locals.eventGroupInfo.marketCount; locals.i++)
        {
            locals.marketId = locals.markets.marketIds.get(locals.i);
            if (input.noMarketMask & (1ULL << locals.i))
            {
                locals.noPositionCount++;
                locals.positionKey = MakePosKey(qpi.invocator(), locals.marketId, QUOTTERY_RESULT_NO);
                if (!state.get().mPositionInfo.get(locals.positionKey, locals.position) ||
                    locals.position.amount < input.amount)
                {
                    return;
                }
                if (locals.position.amount == input.amount)
                {
                    locals.removedPositionCount++;
                }
            }
            else
            {
                locals.positionKey = MakePosKey(qpi.invocator(), locals.marketId, QUOTTERY_RESULT_YES);
                if (state.get().mPositionInfo.get(locals.positionKey, locals.position))
                {
                    if (locals.position.amount > INT64_MAX - input.amount)
                    {
                        return;
                    }
                }
                else
                {
                    locals.newPositionCount++;
                }
            }
        }

        locals.resultingPopulation = state.get().mPositionInfo.population() -
            locals.removedPositionCount + locals.newPositionCount;
        if (locals.resultingPopulation > state.get().mPositionInfo.capacity())
        {
            return;
        }

        if (locals.noPositionCount > 1)
        {
            if (state.get().wholeSharePrice <= 0 ||
                input.amount > MAX_AMOUNT / state.get().wholeSharePrice)
            {
                return;
            }
            locals.collateralPerSet = input.amount * state.get().wholeSharePrice;
            if (locals.collateralPerSet > MAX_AMOUNT / (locals.noPositionCount - 1))
            {
                return;
            }
            output.collateralOut = locals.collateralPerSet * (locals.noPositionCount - 1);

            if (qpi.numberOfShares(
                    state.get().mQUSDIdentifier,
                    { SELF, SELF_INDEX },
                    { SELF, SELF_INDEX }) < output.collateralOut ||
                qpi.transferShareOwnershipAndPossession(
                    state.get().mQUSDIdentifier.assetName,
                    state.get().mQUSDIdentifier.issuer,
                    SELF,
                    SELF,
                    output.collateralOut,
                    qpi.invocator()) < 0)
            {
                output.collateralOut = 0;
                return;
            }
        }

        // Burn the selected NO positions.
        for (locals.i = 0; locals.i < locals.eventGroupInfo.marketCount; locals.i++)
        {
            if (!(input.noMarketMask & (1ULL << locals.i))) continue;

            locals.marketId = locals.markets.marketIds.get(locals.i);
            locals.positionKey = MakePosKey(qpi.invocator(), locals.marketId, QUOTTERY_RESULT_NO);
            state.get().mPositionInfo.get(locals.positionKey, locals.position);
            locals.position.amount -= input.amount;
            if (locals.position.amount)
            {
                state.mut().mPositionInfo.set(locals.positionKey, locals.position);
            }
            else
            {
                state.mut().mPositionInfo.removeByKey(locals.positionKey);
            }
        }

        // Mint the complementary YES positions.
        for (locals.i = 0; locals.i < locals.eventGroupInfo.marketCount; locals.i++)
        {
            if (input.noMarketMask & (1ULL << locals.i)) continue;

            locals.marketId = locals.markets.marketIds.get(locals.i);
            locals.positionKey = MakePosKey(qpi.invocator(), locals.marketId, QUOTTERY_RESULT_YES);
            if (!state.get().mPositionInfo.get(locals.positionKey, locals.position))
            {
                locals.position.entity = qpi.invocator();
                locals.position.amount = 0;
            }
            locals.position.amount += input.amount;
            state.mut().mPositionInfo.set(locals.positionKey, locals.position);
        }

        output.converted = 1;
        locals.log = QuotteryNegRiskConversionLogger{
            0,
            QUOTTERY_CONVERTED_NEG_RISK_POSITIONS,
            qpi.invocator(),
            input.eventGroupId,
            input.noMarketMask,
            input.amount,
            output.collateralOut,
            0
        };
        LOG_INFO(locals.log);
    }

    struct ReverseNegRiskPositions_input
    {
        uint64 eventGroupId;
        uint64 noMarketMask;
        sint64 amount;
    };
    struct ReverseNegRiskPositions_output
    {
        bit converted;
        sint64 collateralIn;
    };
    struct ReverseNegRiskPositions_locals
    {
        uint16 i;
        uint16 noPositionCount;
        uint64 validMarketMask;
        uint64 removedPositionCount;
        uint64 newPositionCount;
        uint64 resultingPopulation;
        uint64 marketId;
        sint64 collateralPerSet;
        uint64 userBalance;
        id positionKey;
        QtryOrder position;
        QtryEventGroupInfo eventGroupInfo;
        QtryEventGroupMarkets markets;
        QuotteryNegRiskConversionLogger log;
    };

    /**
     * @brief Reverses a NegRisk conversion. The caller supplies the YES
     * positions outside noMarketMask and (selectedCount - 1) complete sets of
     * collateral, and receives NO positions selected by noMarketMask.
     */
    PUBLIC_PROCEDURE_WITH_LOCALS(ReverseNegRiskPositions)
    {
        output.converted = 0;
        output.collateralIn = 0;

        if (state.get().mOperationParams.mAntiSpamAmount)
        {
            if (qpi.invocationReward() < state.get().mOperationParams.mAntiSpamAmount) return;
            if (qpi.invocationReward() > state.get().mOperationParams.mAntiSpamAmount)
            {
                qpi.transfer(qpi.invocator(), qpi.invocationReward() - state.get().mOperationParams.mAntiSpamAmount);
            }
        }

        if (input.amount <= 0 || input.amount >= (sint64)QUOTTERY_MAX_AMOUNT || input.noMarketMask == 0)
        {
            return;
        }
        if (!state.get().mEventGroupInfo.get(input.eventGroupId, locals.eventGroupInfo) ||
            locals.eventGroupInfo.mode != QUOTTERY_EVENT_GROUP_MODE_EXCLUSIVE_ONE ||
            locals.eventGroupInfo.status != QUOTTERY_EVENT_GROUP_STATUS_OPEN ||
            locals.eventGroupInfo.marketCount < 2 ||
            state.get().mEventGroupResult.contains(input.eventGroupId) ||
            !state.get().mEventGroupMarkets.get(input.eventGroupId, locals.markets))
        {
            return;
        }

        if (locals.eventGroupInfo.marketCount < QUOTTERY_MAX_MARKETS_PER_EVENT_GROUP)
        {
            locals.validMarketMask = (1ULL << locals.eventGroupInfo.marketCount) - 1;
            if (input.noMarketMask & ~locals.validMarketMask)
            {
                return;
            }
        }

        for (locals.i = 0; locals.i < locals.eventGroupInfo.marketCount; locals.i++)
        {
            locals.marketId = locals.markets.marketIds.get(locals.i);
            if (input.noMarketMask & (1ULL << locals.i))
            {
                locals.noPositionCount++;
                locals.positionKey = MakePosKey(qpi.invocator(), locals.marketId, QUOTTERY_RESULT_NO);
                if (state.get().mPositionInfo.get(locals.positionKey, locals.position))
                {
                    if (locals.position.amount > INT64_MAX - input.amount) return;
                }
                else
                {
                    locals.newPositionCount++;
                }
            }
            else
            {
                locals.positionKey = MakePosKey(qpi.invocator(), locals.marketId, QUOTTERY_RESULT_YES);
                if (!state.get().mPositionInfo.get(locals.positionKey, locals.position) ||
                    locals.position.amount < input.amount)
                {
                    return;
                }
                if (locals.position.amount == input.amount)
                {
                    locals.removedPositionCount++;
                }
            }
        }

        locals.resultingPopulation = state.get().mPositionInfo.population() -
            locals.removedPositionCount + locals.newPositionCount;
        if (locals.resultingPopulation > state.get().mPositionInfo.capacity()) return;

        if (locals.noPositionCount > 1)
        {
            if (state.get().wholeSharePrice <= 0 ||
                input.amount > MAX_AMOUNT / state.get().wholeSharePrice)
            {
                return;
            }
            locals.collateralPerSet = input.amount * state.get().wholeSharePrice;
            if (locals.collateralPerSet > MAX_AMOUNT / (locals.noPositionCount - 1)) return;
            output.collateralIn = locals.collateralPerSet * (locals.noPositionCount - 1);

            locals.userBalance = qpi.numberOfShares(
                state.get().mQUSDIdentifier,
                { qpi.invocator(), SELF_INDEX },
                { qpi.invocator(), SELF_INDEX });
            if (locals.userBalance < (uint64)output.collateralIn ||
                qpi.transferShareOwnershipAndPossession(
                    state.get().mQUSDIdentifier.assetName,
                    state.get().mQUSDIdentifier.issuer,
                    qpi.invocator(),
                    qpi.invocator(),
                    output.collateralIn,
                    SELF) < 0)
            {
                output.collateralIn = 0;
                return;
            }
        }

        // Burn the complementary YES positions.
        for (locals.i = 0; locals.i < locals.eventGroupInfo.marketCount; locals.i++)
        {
            if (input.noMarketMask & (1ULL << locals.i)) continue;
            locals.marketId = locals.markets.marketIds.get(locals.i);
            locals.positionKey = MakePosKey(qpi.invocator(), locals.marketId, QUOTTERY_RESULT_YES);
            state.get().mPositionInfo.get(locals.positionKey, locals.position);
            locals.position.amount -= input.amount;
            if (locals.position.amount)
            {
                state.mut().mPositionInfo.set(locals.positionKey, locals.position);
            }
            else
            {
                state.mut().mPositionInfo.removeByKey(locals.positionKey);
            }
        }

        // Mint the selected NO positions.
        for (locals.i = 0; locals.i < locals.eventGroupInfo.marketCount; locals.i++)
        {
            if (!(input.noMarketMask & (1ULL << locals.i))) continue;
            locals.marketId = locals.markets.marketIds.get(locals.i);
            locals.positionKey = MakePosKey(qpi.invocator(), locals.marketId, QUOTTERY_RESULT_NO);
            if (!state.get().mPositionInfo.get(locals.positionKey, locals.position))
            {
                locals.position.entity = qpi.invocator();
                locals.position.amount = 0;
            }
            locals.position.amount += input.amount;
            state.mut().mPositionInfo.set(locals.positionKey, locals.position);
        }

        output.converted = 1;
        locals.log = QuotteryNegRiskConversionLogger{
            0,
            QUOTTERY_REVERSED_NEG_RISK_POSITIONS,
            qpi.invocator(),
            input.eventGroupId,
            input.noMarketMask,
            input.amount,
            output.collateralIn,
            0
        };
        LOG_INFO(locals.log);
    }

protected:
    struct QuoteNegRiskRoute_input
    {
        uint64 eventGroupId;
        uint64 targetMarketId;
        sint64 amount;
        bit isBuy;
    };
    struct QuoteNegRiskRoute_output
    {
        bit fillable;
        sint64 grossAmount;
        sint64 collateralAmount;
        sint64 netAmountBeforeFees;
        uint64 orderFillCount;
    };
    struct QuoteNegRiskRoute_locals
    {
        uint16 i;
        sint64 firstIndex;
        sint64 secondIndex;
        sint64 remaining;
        sint64 fillAmount;
        sint64 firstPrice;
        sint64 secondPrice;
        sint64 selectedPrice;
        sint64 lineAmount;
        id key;
        id r;
        QtryOrder order;
        QtryEventInfo qei;
        QtryEventGroupInfo eventGroupInfo;
        QtryEventGroupMarkets markets;
        QtryMarketGroupLink targetLink;
        DateAndTime now;
    };

    /**
     * @brief Quotes a complete synthetic YES route without changing state.
     * Buy consumes NO asks or complementary YES bids. Sell consumes NO bids or
     * complementary YES asks. The whole N-1 leg basket must be fillable.
     */
    PRIVATE_FUNCTION_WITH_LOCALS(QuoteNegRiskRoute)
    {
        setMemory(output, 0);
        if (input.amount <= 0 || input.amount >= (sint64)QUOTTERY_MAX_AMOUNT ||
            state.get().wholeSharePrice <= 0)
        {
            return;
        }
        if (!state.get().mEventGroupInfo.get(input.eventGroupId, locals.eventGroupInfo) ||
            locals.eventGroupInfo.mode != QUOTTERY_EVENT_GROUP_MODE_EXCLUSIVE_ONE ||
            locals.eventGroupInfo.status != QUOTTERY_EVENT_GROUP_STATUS_OPEN ||
            locals.eventGroupInfo.marketCount < 2 ||
            state.get().mEventGroupResult.contains(input.eventGroupId) ||
            !state.get().mEventGroupMarkets.get(input.eventGroupId, locals.markets) ||
            !state.get().mMarketGroupLink.get(input.targetMarketId, locals.targetLink) ||
            locals.targetLink.eventGroupId != input.eventGroupId ||
            locals.targetLink.marketIndex >= locals.eventGroupInfo.marketCount ||
            locals.markets.marketIds.get(locals.targetLink.marketIndex) != input.targetMarketId)
        {
            return;
        }

        if (input.amount > MAX_AMOUNT / state.get().wholeSharePrice) return;
        output.collateralAmount = input.amount * state.get().wholeSharePrice;
        if (locals.eventGroupInfo.marketCount > 2)
        {
            if (output.collateralAmount > MAX_AMOUNT / (locals.eventGroupInfo.marketCount - 2))
            {
                setMemory(output, 0);
                return;
            }
            output.collateralAmount *= (locals.eventGroupInfo.marketCount - 2);
        }
        else
        {
            output.collateralAmount = 0;
        }

        locals.now = qpi.now();
        for (locals.i = 0; locals.i < locals.eventGroupInfo.marketCount; locals.i++)
        {
            if (!state.get().mEventInfo.get(locals.markets.marketIds.get(locals.i), locals.qei) ||
                locals.now < locals.qei.openDate || locals.now > locals.qei.endDate)
            {
                setMemory(output, 0);
                return;
            }
            if (locals.i == locals.targetLink.marketIndex) continue;

            locals.remaining = input.amount;
            if (input.isBuy)
            {
                // Direct NO asks and synthetic NO offers backed by YES bids.
                locals.key = MakeOrderKey(
                    locals.markets.marketIds.get(locals.i),
                    QUOTTERY_RESULT_NO,
                    QUOTTERY_ASK_BIT,
                    locals.r);
                locals.firstIndex = state.get().mABOrders.headIndex(locals.key);
                locals.key = MakeOrderKey(
                    locals.markets.marketIds.get(locals.i),
                    QUOTTERY_RESULT_YES,
                    QUOTTERY_BID_BIT,
                    locals.r);
                locals.secondIndex = state.get().mABOrders.headIndex(locals.key);
            }
            else
            {
                // Direct NO bids and synthetic NO demand backed by YES asks.
                locals.key = MakeOrderKey(
                    locals.markets.marketIds.get(locals.i),
                    QUOTTERY_RESULT_NO,
                    QUOTTERY_BID_BIT,
                    locals.r);
                locals.firstIndex = state.get().mABOrders.headIndex(locals.key);
                locals.key = MakeOrderKey(
                    locals.markets.marketIds.get(locals.i),
                    QUOTTERY_RESULT_YES,
                    QUOTTERY_ASK_BIT,
                    locals.r);
                locals.secondIndex = state.get().mABOrders.headIndex(locals.key);
            }

            while (locals.remaining > 0)
            {
                if (locals.firstIndex == NULL_INDEX && locals.secondIndex == NULL_INDEX)
                {
                    setMemory(output, 0);
                    return;
                }

                if (input.isBuy)
                {
                    locals.firstPrice = state.get().wholeSharePrice + 1;
                    locals.secondPrice = state.get().wholeSharePrice + 1;
                    if (locals.firstIndex != NULL_INDEX)
                    {
                        locals.firstPrice = -state.get().mABOrders.priority(locals.firstIndex);
                    }
                    if (locals.secondIndex != NULL_INDEX)
                    {
                        locals.secondPrice = state.get().wholeSharePrice -
                            state.get().mABOrders.priority(locals.secondIndex);
                    }
                }
                else
                {
                    locals.firstPrice = -1;
                    locals.secondPrice = -1;
                    if (locals.firstIndex != NULL_INDEX)
                    {
                        locals.firstPrice = state.get().mABOrders.priority(locals.firstIndex);
                    }
                    if (locals.secondIndex != NULL_INDEX)
                    {
                        locals.secondPrice = state.get().wholeSharePrice +
                            state.get().mABOrders.priority(locals.secondIndex);
                    }
                }

                if ((input.isBuy && locals.firstPrice <= locals.secondPrice) ||
                    (!input.isBuy && locals.firstPrice >= locals.secondPrice))
                {
                    locals.order = state.get().mABOrders.element(locals.firstIndex);
                    locals.selectedPrice = locals.firstPrice;
                    locals.fillAmount = min(locals.remaining, locals.order.amount);
                    if (locals.fillAmount == locals.order.amount)
                    {
                        locals.firstIndex = state.get().mABOrders.nextElementIndex(locals.firstIndex);
                    }
                }
                else
                {
                    locals.order = state.get().mABOrders.element(locals.secondIndex);
                    locals.selectedPrice = locals.secondPrice;
                    locals.fillAmount = min(locals.remaining, locals.order.amount);
                    if (locals.fillAmount == locals.order.amount)
                    {
                        locals.secondIndex = state.get().mABOrders.nextElementIndex(locals.secondIndex);
                    }
                }

                if (locals.fillAmount <= 0 || locals.selectedPrice < 0 ||
                    (locals.selectedPrice && locals.fillAmount > MAX_AMOUNT / locals.selectedPrice))
                {
                    setMemory(output, 0);
                    return;
                }
                locals.lineAmount = locals.fillAmount * locals.selectedPrice;
                if (output.grossAmount > MAX_AMOUNT - locals.lineAmount)
                {
                    setMemory(output, 0);
                    return;
                }
                output.grossAmount += locals.lineAmount;
                output.orderFillCount++;
                if (output.orderFillCount > QUOTTERY_MAX_NEG_RISK_ORDER_FILLS)
                {
                    setMemory(output, 0);
                    return;
                }
                locals.remaining -= locals.fillAmount;
            }
        }

        output.netAmountBeforeFees = output.grossAmount - output.collateralAmount;
        output.fillable = 1;
    }

public:
    struct QuoteNegRiskBuy_input
    {
        uint64 eventGroupId;
        uint64 targetMarketId;
        sint64 amount;
    };
    typedef QuoteNegRiskRoute_output QuoteNegRiskBuy_output;
    struct QuoteNegRiskBuy_locals
    {
        QuoteNegRiskRoute_input quoteInput;
        QuoteNegRiskRoute_output quoteOutput;
    };

    PUBLIC_FUNCTION_WITH_LOCALS(QuoteNegRiskBuy)
    {
        locals.quoteInput.eventGroupId = input.eventGroupId;
        locals.quoteInput.targetMarketId = input.targetMarketId;
        locals.quoteInput.amount = input.amount;
        locals.quoteInput.isBuy = 1;
        CALL(QuoteNegRiskRoute, locals.quoteInput, locals.quoteOutput);
        output = locals.quoteOutput;
    }

    struct QuoteNegRiskSell_input
    {
        uint64 eventGroupId;
        uint64 targetMarketId;
        sint64 amount;
    };
    typedef QuoteNegRiskRoute_output QuoteNegRiskSell_output;
    struct QuoteNegRiskSell_locals
    {
        QuoteNegRiskRoute_input quoteInput;
        QuoteNegRiskRoute_output quoteOutput;
    };

    PUBLIC_FUNCTION_WITH_LOCALS(QuoteNegRiskSell)
    {
        locals.quoteInput.eventGroupId = input.eventGroupId;
        locals.quoteInput.targetMarketId = input.targetMarketId;
        locals.quoteInput.amount = input.amount;
        locals.quoteInput.isBuy = 0;
        CALL(QuoteNegRiskRoute, locals.quoteInput, locals.quoteOutput);
        output = locals.quoteOutput;
    }

    struct BuyNegRiskPosition_input
    {
        uint64 eventGroupId;
        uint64 targetMarketId;
        sint64 amount;
        sint64 maxGrossCost;
    };
    struct BuyNegRiskPosition_output
    {
        bit bought;
        sint64 grossCost;
        sint64 collateralOut;
        sint64 netCost;
        uint64 orderFillCount;
    };
    struct BuyNegRiskPosition_locals
    {
        uint16 i;
        sint64 remaining;
        sint64 fillAmount;
        sint64 firstIndex;
        sint64 secondIndex;
        sint64 firstPrice;
        sint64 secondPrice;
        sint64 selectedPrice;
        sint64 lineAmount;
        uint64 userBalance;
        uint64 contractBalance;
        uint64 marketId;
        bit useFirst;
        id key;
        id r;
        id positionKey;
        QtryOrder order;
        QtryOrder position;
        QtryEventGroupInfo eventGroupInfo;
        QtryEventGroupMarkets markets;
        QtryMarketGroupLink targetLink;
        QuoteNegRiskRoute_input quoteInput;
        QuoteNegRiskRoute_output quoteOutput;
        RewardTransfer_input transferInput;
        RewardTransfer_output transferOutput;
        UpdatePosition_input updateInput;
        UpdatePosition_output updateOutput;
        QuotteryTradeLogger tradeLog;
        QuotteryNegRiskRouteLogger routeLog;
    };

    /**
     * @brief Atomically buys YES in targetMarketId through the NegRisk route.
     * It fills exactly amount NO shares in every other market from either NO
     * asks or complementary YES bids, then converts the basket to target YES.
     */
    PUBLIC_PROCEDURE_WITH_LOCALS(BuyNegRiskPosition)
    {
        setMemory(output, 0);
        if (state.get().mOperationParams.mAntiSpamAmount)
        {
            if (qpi.invocationReward() < state.get().mOperationParams.mAntiSpamAmount) return;
            if (qpi.invocationReward() > state.get().mOperationParams.mAntiSpamAmount)
            {
                qpi.transfer(qpi.invocator(), qpi.invocationReward() - state.get().mOperationParams.mAntiSpamAmount);
            }
        }
        if (input.maxGrossCost < 0) return;

        locals.quoteInput.eventGroupId = input.eventGroupId;
        locals.quoteInput.targetMarketId = input.targetMarketId;
        locals.quoteInput.amount = input.amount;
        locals.quoteInput.isBuy = 1;
        CALL(QuoteNegRiskRoute, locals.quoteInput, locals.quoteOutput);
        if (!locals.quoteOutput.fillable || locals.quoteOutput.grossAmount > input.maxGrossCost)
        {
            return;
        }
        if (!state.get().mEventGroupInfo.get(input.eventGroupId, locals.eventGroupInfo) ||
            !state.get().mEventGroupMarkets.get(input.eventGroupId, locals.markets) ||
            !state.get().mMarketGroupLink.get(input.targetMarketId, locals.targetLink))
        {
            return;
        }

        // Conservatively reserve one position per consumed order plus target.
        if (state.get().mPositionInfo.population() + locals.quoteOutput.orderFillCount + 1 >
            state.get().mPositionInfo.capacity())
        {
            return;
        }
        locals.positionKey = MakePosKey(qpi.invocator(), input.targetMarketId, QUOTTERY_RESULT_YES);
        if (state.get().mPositionInfo.get(locals.positionKey, locals.position) &&
            locals.position.amount > INT64_MAX - input.amount)
        {
            return;
        }

        // Preflight positions created for complementary YES bidders.
        for (locals.i = 0; locals.i < locals.eventGroupInfo.marketCount; locals.i++)
        {
            if (locals.i == locals.targetLink.marketIndex) continue;
            locals.marketId = locals.markets.marketIds.get(locals.i);
            locals.remaining = input.amount;
            locals.key = MakeOrderKey(locals.marketId, QUOTTERY_RESULT_NO, QUOTTERY_ASK_BIT, locals.r);
            locals.firstIndex = state.get().mABOrders.headIndex(locals.key);
            locals.key = MakeOrderKey(locals.marketId, QUOTTERY_RESULT_YES, QUOTTERY_BID_BIT, locals.r);
            locals.secondIndex = state.get().mABOrders.headIndex(locals.key);
            while (locals.remaining > 0)
            {
                locals.firstPrice = state.get().wholeSharePrice + 1;
                locals.secondPrice = state.get().wholeSharePrice + 1;
                if (locals.firstIndex != NULL_INDEX)
                {
                    locals.firstPrice = -state.get().mABOrders.priority(locals.firstIndex);
                }
                if (locals.secondIndex != NULL_INDEX)
                {
                    locals.secondPrice = state.get().wholeSharePrice -
                        state.get().mABOrders.priority(locals.secondIndex);
                }
                locals.useFirst = locals.firstPrice <= locals.secondPrice;
                if (locals.useFirst)
                {
                    locals.order = state.get().mABOrders.element(locals.firstIndex);
                    locals.fillAmount = min(locals.remaining, locals.order.amount);
                    if (locals.fillAmount == locals.order.amount)
                    {
                        locals.firstIndex = state.get().mABOrders.nextElementIndex(locals.firstIndex);
                    }
                }
                else
                {
                    locals.order = state.get().mABOrders.element(locals.secondIndex);
                    locals.positionKey = MakePosKey(locals.order.entity, locals.marketId, QUOTTERY_RESULT_YES);
                    if (state.get().mPositionInfo.get(locals.positionKey, locals.position) &&
                        locals.position.amount > INT64_MAX - input.amount)
                    {
                        return;
                    }
                    locals.fillAmount = min(locals.remaining, locals.order.amount);
                    if (locals.fillAmount == locals.order.amount)
                    {
                        locals.secondIndex = state.get().mABOrders.nextElementIndex(locals.secondIndex);
                    }
                }
                locals.remaining -= locals.fillAmount;
            }
        }

        locals.userBalance = qpi.numberOfShares(
            state.get().mQUSDIdentifier,
            { qpi.invocator(), SELF_INDEX },
            { qpi.invocator(), SELF_INDEX });
        locals.contractBalance = qpi.numberOfShares(
            state.get().mQUSDIdentifier,
            { SELF, SELF_INDEX },
            { SELF, SELF_INDEX });
        if (locals.userBalance < (uint64)locals.quoteOutput.grossAmount ||
            locals.contractBalance < (uint64)locals.quoteOutput.collateralAmount)
        {
            return;
        }
        if (locals.quoteOutput.grossAmount &&
            qpi.transferShareOwnershipAndPossession(
                state.get().mQUSDIdentifier.assetName,
                state.get().mQUSDIdentifier.issuer,
                qpi.invocator(),
                qpi.invocator(),
                locals.quoteOutput.grossAmount,
                SELF) < 0)
        {
            return;
        }

        for (locals.i = 0; locals.i < locals.eventGroupInfo.marketCount; locals.i++)
        {
            if (locals.i == locals.targetLink.marketIndex) continue;
            locals.marketId = locals.markets.marketIds.get(locals.i);
            locals.remaining = input.amount;
            while (locals.remaining > 0)
            {
                locals.key = MakeOrderKey(locals.marketId, QUOTTERY_RESULT_NO, QUOTTERY_ASK_BIT, locals.r);
                locals.firstIndex = state.get().mABOrders.headIndex(locals.key);
                locals.key = MakeOrderKey(locals.marketId, QUOTTERY_RESULT_YES, QUOTTERY_BID_BIT, locals.r);
                locals.secondIndex = state.get().mABOrders.headIndex(locals.key);
                locals.firstPrice = state.get().wholeSharePrice + 1;
                locals.secondPrice = state.get().wholeSharePrice + 1;
                if (locals.firstIndex != NULL_INDEX)
                {
                    locals.firstPrice = -state.get().mABOrders.priority(locals.firstIndex);
                }
                if (locals.secondIndex != NULL_INDEX)
                {
                    locals.secondPrice = state.get().wholeSharePrice -
                        state.get().mABOrders.priority(locals.secondIndex);
                }
                locals.useFirst = locals.firstPrice <= locals.secondPrice;
                if (locals.useFirst)
                {
                    locals.order = state.get().mABOrders.element(locals.firstIndex);
                    locals.selectedPrice = locals.firstPrice;
                }
                else
                {
                    locals.order = state.get().mABOrders.element(locals.secondIndex);
                    locals.selectedPrice = locals.secondPrice;
                }
                locals.fillAmount = min(locals.remaining, locals.order.amount);
                locals.lineAmount = locals.fillAmount * locals.selectedPrice;

                if (locals.useFirst)
                {
                    locals.transferInput.amount = locals.lineAmount;
                    locals.transferInput.eid = locals.marketId;
                    locals.transferInput.receiver = locals.order.entity;
                    locals.transferInput.needChargeFee = 1;
                    CALL(RewardTransfer, locals.transferInput, locals.transferOutput);
                    if (!locals.transferOutput.ok) return;

                    locals.tradeLog = QuotteryTradeLogger{
                        0, QUOTTERY_MATCH_TYPE_0, locals.order.entity, qpi.invocator(),
                        locals.marketId, QUOTTERY_RESULT_NO, 0, 0,
                        locals.fillAmount, locals.selectedPrice, 0, 0
                    };
                    LOG_INFO(locals.tradeLog);
                    locals.order.amount -= locals.fillAmount;
                    if (locals.order.amount)
                    {
                        state.mut().mABOrders.replace(locals.firstIndex, locals.order);
                    }
                    else
                    {
                        state.mut().mABOrders.remove(locals.firstIndex);
                    }
                }
                else
                {
                    locals.updateInput.uid = locals.order.entity;
                    locals.updateInput.amountChange = locals.fillAmount;
                    locals.updateInput.oi.eid = locals.marketId;
                    locals.updateInput.oi.option = QUOTTERY_RESULT_YES;
                    locals.updateInput.oi.tradeBit = QUOTTERY_BID_BIT;
                    CALL(UpdatePosition, locals.updateInput, locals.updateOutput);
                    if (!locals.updateOutput.ok) return;

                    locals.tradeLog = QuotteryTradeLogger{
                        0, QUOTTERY_MATCH_TYPE_3, qpi.invocator(), locals.order.entity,
                        locals.marketId, 2, 0, 0, locals.fillAmount,
                        locals.selectedPrice, state.get().wholeSharePrice - locals.selectedPrice, 0
                    };
                    LOG_INFO(locals.tradeLog);
                    locals.order.amount -= locals.fillAmount;
                    if (locals.order.amount)
                    {
                        state.mut().mABOrders.replace(locals.secondIndex, locals.order);
                    }
                    else
                    {
                        state.mut().mABOrders.remove(locals.secondIndex);
                    }
                }
                locals.remaining -= locals.fillAmount;
            }
        }

        locals.updateInput.uid = qpi.invocator();
        locals.updateInput.amountChange = input.amount;
        locals.updateInput.oi.eid = input.targetMarketId;
        locals.updateInput.oi.option = QUOTTERY_RESULT_YES;
        locals.updateInput.oi.tradeBit = QUOTTERY_BID_BIT;
        CALL(UpdatePosition, locals.updateInput, locals.updateOutput);
        if (!locals.updateOutput.ok) return;

        if (locals.quoteOutput.collateralAmount)
        {
            locals.transferInput.amount = locals.quoteOutput.collateralAmount;
            locals.transferInput.eid = input.targetMarketId;
            locals.transferInput.receiver = qpi.invocator();
            locals.transferInput.needChargeFee = 0;
            CALL(RewardTransfer, locals.transferInput, locals.transferOutput);
            if (!locals.transferOutput.ok) return;
        }

        output.bought = 1;
        output.grossCost = locals.quoteOutput.grossAmount;
        output.collateralOut = locals.quoteOutput.collateralAmount;
        output.netCost = locals.quoteOutput.netAmountBeforeFees;
        output.orderFillCount = locals.quoteOutput.orderFillCount;
        locals.routeLog = QuotteryNegRiskRouteLogger{
            0, QUOTTERY_BOUGHT_NEG_RISK_POSITION, qpi.invocator(),
            input.eventGroupId, input.targetMarketId, input.amount,
            output.grossCost, output.collateralOut, output.orderFillCount, 0
        };
        LOG_INFO(locals.routeLog);
    }

    struct SellNegRiskPosition_input
    {
        uint64 eventGroupId;
        uint64 targetMarketId;
        sint64 amount;
        sint64 minGrossProceeds;
    };
    struct SellNegRiskPosition_output
    {
        bit sold;
        sint64 grossProceeds;
        sint64 collateralIn;
        sint64 netProceedsBeforeFees;
        uint64 orderFillCount;
    };
    struct SellNegRiskPosition_locals
    {
        uint16 i;
        sint64 remaining;
        sint64 fillAmount;
        sint64 firstIndex;
        sint64 secondIndex;
        sint64 firstPrice;
        sint64 secondPrice;
        sint64 selectedPrice;
        sint64 lineAmount;
        sint64 yesPrice;
        sint64 requiredPayout;
        uint64 userBalance;
        uint64 contractBalance;
        uint64 marketId;
        bit useFirst;
        id key;
        id r;
        id positionKey;
        QtryOrder order;
        QtryOrder position;
        QtryEventGroupInfo eventGroupInfo;
        QtryEventGroupMarkets markets;
        QtryMarketGroupLink targetLink;
        QuoteNegRiskRoute_input quoteInput;
        QuoteNegRiskRoute_output quoteOutput;
        RewardTransfer_input transferInput;
        RewardTransfer_output transferOutput;
        UpdatePosition_input updateInput;
        UpdatePosition_output updateOutput;
        QuotteryTradeLogger tradeLog;
        QuotteryNegRiskRouteLogger routeLog;
    };

    /**
     * @brief Atomically sells target YES through its equivalent NO basket. The
     * caller supplies (N-2) collateral sets; the procedure fills NO demand in
     * every other market and consumes the target YES position.
     */
    PUBLIC_PROCEDURE_WITH_LOCALS(SellNegRiskPosition)
    {
        setMemory(output, 0);
        if (state.get().mOperationParams.mAntiSpamAmount)
        {
            if (qpi.invocationReward() < state.get().mOperationParams.mAntiSpamAmount) return;
            if (qpi.invocationReward() > state.get().mOperationParams.mAntiSpamAmount)
            {
                qpi.transfer(qpi.invocator(), qpi.invocationReward() - state.get().mOperationParams.mAntiSpamAmount);
            }
        }
        if (input.minGrossProceeds < 0) return;

        locals.quoteInput.eventGroupId = input.eventGroupId;
        locals.quoteInput.targetMarketId = input.targetMarketId;
        locals.quoteInput.amount = input.amount;
        locals.quoteInput.isBuy = 0;
        CALL(QuoteNegRiskRoute, locals.quoteInput, locals.quoteOutput);
        if (!locals.quoteOutput.fillable ||
            locals.quoteOutput.grossAmount < input.minGrossProceeds)
        {
            return;
        }
        if (!state.get().mEventGroupInfo.get(input.eventGroupId, locals.eventGroupInfo) ||
            !state.get().mEventGroupMarkets.get(input.eventGroupId, locals.markets) ||
            !state.get().mMarketGroupLink.get(input.targetMarketId, locals.targetLink))
        {
            return;
        }

        locals.positionKey = MakePosKey(qpi.invocator(), input.targetMarketId, QUOTTERY_RESULT_YES);
        if (!state.get().mPositionInfo.get(locals.positionKey, locals.position) ||
            locals.position.amount < input.amount)
        {
            return;
        }
        if (state.get().mPositionInfo.population() + locals.quoteOutput.orderFillCount >
            state.get().mPositionInfo.capacity())
        {
            return;
        }

        // Preflight positions created for direct NO bidders.
        for (locals.i = 0; locals.i < locals.eventGroupInfo.marketCount; locals.i++)
        {
            if (locals.i == locals.targetLink.marketIndex) continue;
            locals.marketId = locals.markets.marketIds.get(locals.i);
            locals.remaining = input.amount;
            locals.key = MakeOrderKey(locals.marketId, QUOTTERY_RESULT_NO, QUOTTERY_BID_BIT, locals.r);
            locals.firstIndex = state.get().mABOrders.headIndex(locals.key);
            locals.key = MakeOrderKey(locals.marketId, QUOTTERY_RESULT_YES, QUOTTERY_ASK_BIT, locals.r);
            locals.secondIndex = state.get().mABOrders.headIndex(locals.key);
            while (locals.remaining > 0)
            {
                locals.firstPrice = -1;
                locals.secondPrice = -1;
                if (locals.firstIndex != NULL_INDEX)
                {
                    locals.firstPrice = state.get().mABOrders.priority(locals.firstIndex);
                }
                if (locals.secondIndex != NULL_INDEX)
                {
                    locals.secondPrice = state.get().wholeSharePrice +
                        state.get().mABOrders.priority(locals.secondIndex);
                }
                locals.useFirst = locals.firstPrice >= locals.secondPrice;
                if (locals.useFirst)
                {
                    locals.order = state.get().mABOrders.element(locals.firstIndex);
                    locals.positionKey = MakePosKey(
                        locals.order.entity, locals.marketId, QUOTTERY_RESULT_NO);
                    if (state.get().mPositionInfo.get(locals.positionKey, locals.position) &&
                        locals.position.amount > INT64_MAX - input.amount)
                    {
                        return;
                    }
                    locals.fillAmount = min(locals.remaining, locals.order.amount);
                    locals.lineAmount = locals.fillAmount * locals.firstPrice;
                    if (locals.fillAmount == locals.order.amount)
                    {
                        locals.firstIndex = state.get().mABOrders.nextElementIndex(locals.firstIndex);
                    }
                }
                else
                {
                    locals.order = state.get().mABOrders.element(locals.secondIndex);
                    locals.fillAmount = min(locals.remaining, locals.order.amount);
                    locals.lineAmount = locals.fillAmount * state.get().wholeSharePrice;
                    if (locals.fillAmount == locals.order.amount)
                    {
                        locals.secondIndex = state.get().mABOrders.nextElementIndex(locals.secondIndex);
                    }
                }
                if (locals.requiredPayout > MAX_AMOUNT - locals.lineAmount) return;
                locals.requiredPayout += locals.lineAmount;
                locals.remaining -= locals.fillAmount;
            }
        }

        locals.userBalance = qpi.numberOfShares(
            state.get().mQUSDIdentifier,
            { qpi.invocator(), SELF_INDEX },
            { qpi.invocator(), SELF_INDEX });
        if (locals.userBalance < (uint64)locals.quoteOutput.collateralAmount) return;

        locals.contractBalance = qpi.numberOfShares(
            state.get().mQUSDIdentifier,
            { SELF, SELF_INDEX },
            { SELF, SELF_INDEX });
        if (locals.requiredPayout > locals.quoteOutput.collateralAmount &&
            locals.contractBalance <
                (uint64)(locals.requiredPayout - locals.quoteOutput.collateralAmount))
        {
            return;
        }

        if (locals.quoteOutput.collateralAmount &&
            qpi.transferShareOwnershipAndPossession(
                state.get().mQUSDIdentifier.assetName,
                state.get().mQUSDIdentifier.issuer,
                qpi.invocator(),
                qpi.invocator(),
                locals.quoteOutput.collateralAmount,
                SELF) < 0)
        {
            return;
        }

        locals.positionKey = MakePosKey(
            qpi.invocator(), input.targetMarketId, QUOTTERY_RESULT_YES);
        if (!state.get().mPositionInfo.get(locals.positionKey, locals.position) ||
            locals.position.amount < input.amount)
        {
            return;
        }
        locals.position.amount -= input.amount;
        if (locals.position.amount)
        {
            state.mut().mPositionInfo.set(locals.positionKey, locals.position);
        }
        else
        {
            state.mut().mPositionInfo.removeByKey(locals.positionKey);
        }

        for (locals.i = 0; locals.i < locals.eventGroupInfo.marketCount; locals.i++)
        {
            if (locals.i == locals.targetLink.marketIndex) continue;
            locals.marketId = locals.markets.marketIds.get(locals.i);
            locals.remaining = input.amount;
            while (locals.remaining > 0)
            {
                locals.key = MakeOrderKey(locals.marketId, QUOTTERY_RESULT_NO, QUOTTERY_BID_BIT, locals.r);
                locals.firstIndex = state.get().mABOrders.headIndex(locals.key);
                locals.key = MakeOrderKey(locals.marketId, QUOTTERY_RESULT_YES, QUOTTERY_ASK_BIT, locals.r);
                locals.secondIndex = state.get().mABOrders.headIndex(locals.key);
                locals.firstPrice = -1;
                locals.secondPrice = -1;
                if (locals.firstIndex != NULL_INDEX)
                {
                    locals.firstPrice = state.get().mABOrders.priority(locals.firstIndex);
                }
                if (locals.secondIndex != NULL_INDEX)
                {
                    locals.secondPrice = state.get().wholeSharePrice +
                        state.get().mABOrders.priority(locals.secondIndex);
                }
                locals.useFirst = locals.firstPrice >= locals.secondPrice;
                if (locals.useFirst)
                {
                    locals.order = state.get().mABOrders.element(locals.firstIndex);
                    locals.selectedPrice = locals.firstPrice;
                }
                else
                {
                    locals.order = state.get().mABOrders.element(locals.secondIndex);
                    locals.selectedPrice = locals.secondPrice;
                }
                locals.fillAmount = min(locals.remaining, locals.order.amount);
                locals.lineAmount = locals.fillAmount * locals.selectedPrice;

                if (locals.lineAmount)
                {
                    locals.transferInput.amount = locals.lineAmount;
                    locals.transferInput.eid = locals.marketId;
                    locals.transferInput.receiver = qpi.invocator();
                    locals.transferInput.needChargeFee = 1;
                    CALL(RewardTransfer, locals.transferInput, locals.transferOutput);
                    if (!locals.transferOutput.ok) return;
                }

                if (locals.useFirst)
                {
                    locals.updateInput.uid = locals.order.entity;
                    locals.updateInput.amountChange = locals.fillAmount;
                    locals.updateInput.oi.eid = locals.marketId;
                    locals.updateInput.oi.option = QUOTTERY_RESULT_NO;
                    locals.updateInput.oi.tradeBit = QUOTTERY_BID_BIT;
                    CALL(UpdatePosition, locals.updateInput, locals.updateOutput);
                    if (!locals.updateOutput.ok) return;

                    locals.tradeLog = QuotteryTradeLogger{
                        0, QUOTTERY_MATCH_TYPE_0, qpi.invocator(), locals.order.entity,
                        locals.marketId, QUOTTERY_RESULT_NO, 0, 0,
                        locals.fillAmount, locals.selectedPrice, 0, 0
                    };
                    LOG_INFO(locals.tradeLog);
                    locals.order.amount -= locals.fillAmount;
                    if (locals.order.amount)
                    {
                        state.mut().mABOrders.replace(locals.firstIndex, locals.order);
                    }
                    else
                    {
                        state.mut().mABOrders.remove(locals.firstIndex);
                    }
                }
                else
                {
                    locals.yesPrice = state.get().wholeSharePrice - locals.selectedPrice;
                    locals.transferInput.amount = locals.fillAmount * locals.yesPrice;
                    locals.transferInput.eid = locals.marketId;
                    locals.transferInput.receiver = locals.order.entity;
                    locals.transferInput.needChargeFee = 1;
                    CALL(RewardTransfer, locals.transferInput, locals.transferOutput);
                    if (!locals.transferOutput.ok) return;

                    locals.tradeLog = QuotteryTradeLogger{
                        0, QUOTTERY_MATCH_TYPE_2, qpi.invocator(), locals.order.entity,
                        locals.marketId, 2, 0, 0, locals.fillAmount,
                        locals.selectedPrice, locals.yesPrice, 0
                    };
                    LOG_INFO(locals.tradeLog);
                    locals.order.amount -= locals.fillAmount;
                    if (locals.order.amount)
                    {
                        state.mut().mABOrders.replace(locals.secondIndex, locals.order);
                    }
                    else
                    {
                        state.mut().mABOrders.remove(locals.secondIndex);
                    }
                }
                locals.remaining -= locals.fillAmount;
            }
        }

        output.sold = 1;
        output.grossProceeds = locals.quoteOutput.grossAmount;
        output.collateralIn = locals.quoteOutput.collateralAmount;
        output.netProceedsBeforeFees = locals.quoteOutput.netAmountBeforeFees;
        output.orderFillCount = locals.quoteOutput.orderFillCount;
        locals.routeLog = QuotteryNegRiskRouteLogger{
            0, QUOTTERY_SOLD_NEG_RISK_POSITION, qpi.invocator(),
            input.eventGroupId, input.targetMarketId, input.amount,
            output.grossProceeds, output.collateralIn, output.orderFillCount, 0
        };
        LOG_INFO(locals.routeLog);
    }

    struct MatchEventGroupOrders_input
    {
        uint64 eventGroupId;
        uint64 maxOrderFills;
    };

    struct MatchEventGroupOrders_output
    {
        uint64 mintOrderFillCount;
        uint64 mergeOrderFillCount;
        uint64 mintMatchCount;
        uint64 mergeMatchCount;
    };

    struct MatchEventGroupOrders_locals
    {
        uint64 maxOrderFills;
        QtryEventGroupInfo eventGroupInfo;
        QtryEventGroupMarkets markets;
        MatchingEventGroupOrders_input matchInput;
        MatchingEventGroupOrders_output matchOutput;
    };

    /**
     * @brief Permissionless bounded crank for complete-set group MINT/MERGE.
     * Normal order placement invokes the same matcher automatically; this
     * procedure lets any caller retry old resting books without controlling
     * settlement prices or recipients.
     */
    PUBLIC_PROCEDURE_WITH_LOCALS(MatchEventGroupOrders)
    {
        setMemory(output, 0);
        if (state.get().mOperationParams.mAntiSpamAmount)
        {
            if (qpi.invocationReward() < state.get().mOperationParams.mAntiSpamAmount) return;
            if (qpi.invocationReward() > state.get().mOperationParams.mAntiSpamAmount)
            {
                qpi.transfer(
                    qpi.invocator(),
                    qpi.invocationReward() - state.get().mOperationParams.mAntiSpamAmount);
            }
        }

        if (!state.get().mEventGroupInfo.get(input.eventGroupId, locals.eventGroupInfo) ||
            !state.get().mEventGroupMarkets.get(input.eventGroupId, locals.markets) ||
            locals.eventGroupInfo.marketCount < 2)
        {
            return;
        }

        locals.maxOrderFills = input.maxOrderFills;
        if (locals.maxOrderFills == 0 ||
            locals.maxOrderFills > QUOTTERY_MAX_NEG_RISK_ORDER_FILLS)
        {
            locals.maxOrderFills = QUOTTERY_MAX_NEG_RISK_ORDER_FILLS;
        }

        locals.matchInput.eventGroupId = input.eventGroupId;
        locals.matchInput.preferredMarketId = locals.markets.marketIds.get(0);
        locals.matchInput.maxOrderFills = locals.maxOrderFills;
        locals.matchInput.isBid = 1;
        CALL(MatchingEventGroupOrders, locals.matchInput, locals.matchOutput);
        output.mintOrderFillCount = locals.matchOutput.orderFillCount;
        output.mintMatchCount = locals.matchOutput.matchCount;

        if (output.mintOrderFillCount < locals.maxOrderFills)
        {
            locals.matchInput.maxOrderFills =
                locals.maxOrderFills - output.mintOrderFillCount;
            locals.matchInput.isBid = 0;
            CALL(MatchingEventGroupOrders, locals.matchInput, locals.matchOutput);
            output.mergeOrderFillCount = locals.matchOutput.orderFillCount;
            output.mergeMatchCount = locals.matchOutput.matchCount;
        }
    }

    struct PublishResult_locals
    {
        QtryEventInfo qei;
        QtryMarketGroupLink marketGroupLink;
        QtryEventGroupInfo eventGroupInfo;
        QuotteryLoggerWithData log;
        DepositInfo di;
        sint8 existingResult;
    };

    struct PublishResult_input
    {
        uint64 eventId;
        uint64 option;
    };
    struct PublishResult_output
    {
    };
    /**
    * Publish result of a event (GO only)
    * GO is required to LOCK mDepositAmountForDispute for publishing each result
    * @param eventId (8 bytes)
    * @param option (8 bytes): winning option
    */
    PUBLIC_PROCEDURE_WITH_LOCALS(PublishResult)
    {
        if (qpi.invocator() != state.get().mQtryGov.mOperationId)
        {
            return;
        }
        // deposit
        if (qpi.invocationReward() != state.get().mQtryGov.mDepositAmountForDispute)
        {
            if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
            return;
        }

        if (!isOptionValid(input.option))
        {
            if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
            return;
        }

        if (!state.get().mEventInfo.get(input.eventId, locals.qei))
        {
            if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
            return;
        }

        // EXCLUSIVE_ONE has a single group-level result and dispute deposit.
        // Publishing its child markets independently could create multiple
        // winners, so it must use PublishEventResult instead.
        if (state.get().mMarketGroupLink.get(input.eventId, locals.marketGroupLink) &&
            state.get().mEventGroupInfo.get(locals.marketGroupLink.eventGroupId, locals.eventGroupInfo) &&
            locals.eventGroupInfo.mode == QUOTTERY_EVENT_GROUP_MODE_EXCLUSIVE_ONE)
        {
            if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
            return;
        }

        if (qpi.now() < locals.qei.endDate)
        {
            if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
            return;
        }

        // prevent re-publishing (deposit loss, timer reset, result flip)
        state.get().mEventResult.get(input.eventId, locals.existingResult);
        if (locals.existingResult != QUOTTERY_RESULT_NOT_SET)
        {
            if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
            return;
        }

        locals.di.pubkey = qpi.invocator();
        locals.di.amount = qpi.invocationReward();
        state.mut().mGODepositInfo.set(input.eventId, locals.di);
        state.mut().mEventResult.set(input.eventId, sint8(input.option));
        state.mut().mEventResultPublishTickTime.set(input.eventId, qpi.tick());
        locals.log = QuotteryLoggerWithData{ 0, QUOTTERY_PUBLISH_RESULT, id(0,0,input.eventId,input.option), 0 };
        LOG_INFO(locals.log);
    }

    struct PublishEventResult_input
    {
        uint64 eventGroupId;
        uint64 winningMarketId;
    };
    struct PublishEventResult_output
    {
        bit published;
    };
    struct PublishEventResult_locals
    {
        uint16 i;
        uint32 publishTick;
        QtryEventGroupInfo eventGroupInfo;
        QtryEventGroupMarkets markets;
        QtryMarketGroupLink winningMarketLink;
        QtryEventInfo qei;
        DepositInfo di;
        QuotteryLoggerWithData log;
    };

    PUBLIC_PROCEDURE_WITH_LOCALS(PublishEventResult)
    {
        if (qpi.invocator() != state.get().mQtryGov.mOperationId)
        {
            if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
            return;
        }
        if (qpi.invocationReward() != state.get().mQtryGov.mDepositAmountForDispute)
        {
            if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
            return;
        }
        if (!state.get().mEventGroupInfo.get(input.eventGroupId, locals.eventGroupInfo) ||
            locals.eventGroupInfo.mode != QUOTTERY_EVENT_GROUP_MODE_EXCLUSIVE_ONE ||
            locals.eventGroupInfo.status != QUOTTERY_EVENT_GROUP_STATUS_OPEN ||
            state.get().mEventGroupResult.contains(input.eventGroupId))
        {
            if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
            return;
        }
        if (!state.get().mMarketGroupLink.get(input.winningMarketId, locals.winningMarketLink) ||
            locals.winningMarketLink.eventGroupId != input.eventGroupId ||
            !state.get().mEventGroupMarkets.get(input.eventGroupId, locals.markets))
        {
            if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
            return;
        }

        for (locals.i = 0; locals.i < locals.eventGroupInfo.marketCount; locals.i++)
        {
            if (!state.get().mEventInfo.get(locals.markets.marketIds.get(locals.i), locals.qei) ||
                qpi.now() < locals.qei.endDate)
            {
                if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
                return;
            }
        }

        locals.di.pubkey = qpi.invocator();
        locals.di.amount = qpi.invocationReward();
        locals.publishTick = qpi.tick();
        state.mut().mEventGroupGODepositInfo.set(input.eventGroupId, locals.di);
        state.mut().mEventGroupResult.set(input.eventGroupId, (sint8)locals.winningMarketLink.marketIndex);
        state.mut().mEventGroupResultPublishTickTime.set(input.eventGroupId, locals.publishTick);
        state.mut().mEventGroupDisputeResolved.removeByKey(input.eventGroupId);

        for (locals.i = 0; locals.i < locals.eventGroupInfo.marketCount; locals.i++)
        {
            if (locals.i == locals.winningMarketLink.marketIndex)
            {
                state.mut().mEventResult.set(locals.markets.marketIds.get(locals.i), QUOTTERY_RESULT_YES);
            }
            else
            {
                state.mut().mEventResult.set(locals.markets.marketIds.get(locals.i), QUOTTERY_RESULT_NO);
            }
            state.mut().mEventResultPublishTickTime.set(locals.markets.marketIds.get(locals.i), locals.publishTick);
        }

        locals.eventGroupInfo.status = QUOTTERY_EVENT_GROUP_STATUS_RESOLVING;
        state.mut().mEventGroupInfo.set(input.eventGroupId, locals.eventGroupInfo);
        output.published = 1;
        locals.log = QuotteryLoggerWithData{
            0,
            QUOTTERY_PUBLISHED_EVENT_GROUP_RESULT,
            id(0, locals.winningMarketLink.marketIndex, input.eventGroupId, input.winningMarketId),
            0
        };
        LOG_INFO(locals.log);
    }

    struct GetOrders_input
    {
        uint64 eventId;
        uint64 option;
        uint64 isBid;
        uint64 offset;
    };
    struct GetOrders_output
    {
        struct QtryOrderWithPrice
        {
            QtryOrder qo;
            sint64 price;
        };
        Array<QtryOrderWithPrice, 256> orders;
    };
    struct GetOrders_locals
    {
        sint64 i, c, sign;
        id key, r;
        GetOrders_output::QtryOrderWithPrice order;
    };
    /**
     * @brief PUBLIC VIEW FUNCTION
     * Retrieves a paginated list of orders from the order book for a specific side of an event.
     * @param eventId The event to query.
     * @param option The option (0 or 1).
     * @param isBid 1 for bids (buy orders), 0 for asks (sell orders).
     * @param offset The number of orders to skip (for pagination).
     * @return A list of up to 256 orders with their price and amount.
     */
    PUBLIC_FUNCTION_WITH_LOCALS(GetOrders)
    {
        setMemory(output, 0);
        if (input.option > 1) return;
        if (!state.get().mEventInfo.contains(input.eventId)) return;
        locals.key = MakeOrderKey(input.eventId, input.option, input.isBid, locals.r);
        locals.i = state.get().mABOrders.headIndex(locals.key);
        locals.c = 0;
        if (input.isBid) locals.sign = 1;
        else locals.sign = -1;
        while (locals.i != NULL_INDEX && locals.c < 256)
        {
            if (input.offset)
            {
                input.offset--;
            }
            else
            {
                locals.order.price = locals.sign * state.get().mABOrders.priority(locals.i);
                locals.order.qo = state.get().mABOrders.element(locals.i);
                output.orders.set(locals.c++, locals.order);
            }
            locals.i = state.get().mABOrders.nextElementIndex(locals.i);
        }
    }

    struct UpdateFeeDiscountList_input
    {
        id userId;
        uint64 newFeeRate;
        uint64 ops; // 0 remove, 1 set (add/update)
    };
    struct UpdateFeeDiscountList_output {};
    struct UpdateFeeDiscountList_locals
    {
        QuotteryLoggerWithData log;
    };

    PUBLIC_PROCEDURE_WITH_LOCALS(UpdateFeeDiscountList)
    {
        if (qpi.invocationReward()) qpi.transfer(qpi.invocator(), qpi.invocationReward());
        if (qpi.invocator() != state.get().mQtryGov.mOperationId) return;

        locals.log = QuotteryLoggerWithData{ 0, QUOTTERY_UPDATED_NEW_DISCOUNT_FEE, input.userId, 0 };
        LOG_INFO(locals.log);

        if (input.ops == 0)
        {
            state.mut().mOperationParams.discountedFeeForUsers.removeByKey(input.userId);
            return;
        }
        else
        {
            // cap discount rate to prevent underflow in fee calculation
            if (input.newFeeRate > QUOTTERY_PERCENT_DENOMINATOR) return;
            state.mut().mOperationParams.discountedFeeForUsers.set(input.userId, input.newFeeRate);
            return;
        }
    }

    REGISTER_USER_FUNCTIONS_AND_PROCEDURES()
    {
        // FUNCTION (view)
        REGISTER_USER_FUNCTION(BasicInfo, 1);
        REGISTER_USER_FUNCTION(GetEventInfo, 2);
        REGISTER_USER_FUNCTION(GetOrders, 3);
        REGISTER_USER_FUNCTION(GetActiveEvent, 4);
        REGISTER_USER_FUNCTION(GetEventInfoBatch, 5);
        REGISTER_USER_FUNCTION(GetUserPosition, 6);
        REGISTER_USER_FUNCTION(GetApprovedAmount, 7);
        REGISTER_USER_FUNCTION(GetTopProposals, 8);
        REGISTER_USER_FUNCTION(GetEventGroup, 9);
        REGISTER_USER_FUNCTION(GetMarketEventGroup, 10);
        REGISTER_USER_FUNCTION(GetEventGroupInfoBatch, 11);
        REGISTER_USER_FUNCTION(QuoteNegRiskBuy, 12);
        REGISTER_USER_FUNCTION(QuoteNegRiskSell, 13);

        REGISTER_USER_PROCEDURE(CreateEvent, 1);
        REGISTER_USER_PROCEDURE(AddToAskOrder, 2);
        REGISTER_USER_PROCEDURE(RemoveAskOrder, 3);
        REGISTER_USER_PROCEDURE(AddToBidOrder, 4);
        REGISTER_USER_PROCEDURE(RemoveBidOrder, 5);
        REGISTER_USER_PROCEDURE(PublishResult, 6);
        REGISTER_USER_PROCEDURE(TryFinalizeEvent, 7);
        REGISTER_USER_PROCEDURE(Dispute, 8);
        REGISTER_USER_PROCEDURE(ResolveDispute, 9);
        REGISTER_USER_PROCEDURE(UserClaimReward, 10);
        REGISTER_USER_PROCEDURE(GOForceClaimReward, 11);
        REGISTER_USER_PROCEDURE(TransferQUSD, 12);
        REGISTER_USER_PROCEDURE(TransferShareManagementRights, 13);
        REGISTER_USER_PROCEDURE(CleanMemory, 14);
        REGISTER_USER_PROCEDURE(TransferQTRYGOV, 15);

        // operation team proc
        REGISTER_USER_PROCEDURE(UpdateFeeDiscountList, 20);

        // event group procedures
        REGISTER_USER_PROCEDURE(CreateEventGroup, 30);
        REGISTER_USER_PROCEDURE(AddMarket, 31);
        REGISTER_USER_PROCEDURE(OpenEvent, 32);
        REGISTER_USER_PROCEDURE(PublishEventResult, 33);
        REGISTER_USER_PROCEDURE(DisputeEventResult, 34);
        REGISTER_USER_PROCEDURE(ResolveEventDispute, 35);
        REGISTER_USER_PROCEDURE(CancelEventGroup, 36);
        REGISTER_USER_PROCEDURE(ConvertNegRiskPositions, 37);
        REGISTER_USER_PROCEDURE(ReverseNegRiskPositions, 38);
        REGISTER_USER_PROCEDURE(BuyNegRiskPosition, 39);
        REGISTER_USER_PROCEDURE(SellNegRiskPosition, 40);
        REGISTER_USER_PROCEDURE(MatchEventGroupOrders, 41);

        // Shareholder proposals: use standard function/procedure indices
        REGISTER_USER_PROCEDURE(ProposalVote, 100);
    }

    typedef NoData Reinit_input;
    typedef NoData Reinit_output;
    struct Reinit_locals {
        id dst;
        AssetPossessionIterator qtryIterator;
        Asset qtryAsset;
    };

    PRIVATE_PROCEDURE_WITH_LOCALS(Reinit)
    {
        state.mut().mOperationParams.mAntiSpamAmount = 11;
        state.mut().mOperationParams.discountedFeeForUsers.cleanup();
        setMemory(state.mut().mQtryGov, 0);
        state.mut().mQtryGov.mOperationId = ID(_V, _A, _E, _F, _X, _O, _E, _V, _K, _P, _O, _X, _B, _A, _R, _T, _U, _T, _B, _M, _C, _P, _L, _T, _V, _G, _I, _B, _Z, _N, _C, _Y, _K, _K, _W, _X, _U, _V, _F, _N, _G, _G, _Q, _M, _F, _P, _X, _E, _E, _F, _X, _F, _F, _O, _E, _E);
        state.mut().mQtryGov.mBurnFee = 0;
        state.mut().mQtryGov.mOperationFee = 50; // 5%
        state.mut().mQtryGov.mShareHolderFee = 0; // 0%
        state.mut().mQtryGov.mDepositAmountForDispute = 1000000000;
        state.mut().mRecentActiveEvent.setAll(NULL_INDEX);
        state.mut().wholeSharePrice = 100000;

        qpi.issueAsset(24294015856956497ULL, SELF, 0, 676, 0); // mQTRYGOVIdentifier
        state.mut().mQTRYGOVIdentifier.assetName = 24294015856956497ULL;
        state.mut().mQTRYGOVIdentifier.issuer = SELF;

        // temp replacement for mQUSDIdentifier
        state.mut().mQUSDIdentifier.assetName = 310652322119ULL; // GARTH
        state.mut().mQUSDIdentifier.issuer = ID(_P, _H, _O, _E, _N, _I, _X, _C, _L, _Q, _O, _B, _H, _D, _Z, _C, _H, _J, _O, _C, _K, _C, _P, _Z, _V, _T, _K, _A, _L, _Q, _B, _M, _X, _Y, _O, _E, _D, _B, _U, _H, _S, _D, _C, _J, _R, _M, _T, _U, _C, _U, _B, _P, _L, _S, _U, _F);
        
        // distribute mQTRYGOVIdentifier to current shareholders
        locals.qtryAsset.assetName = QUOTTERY_CONTRACT_ASSET_NAME;
        locals.qtryAsset.issuer = NULL_ID;

        // distribute QTRY GOV to current shareholders
        for (locals.qtryIterator.begin(locals.qtryAsset); !locals.qtryIterator.reachedEnd(); locals.qtryIterator.next())
        {
            if (locals.qtryIterator.numberOfOwnedShares() > 0)
            {
                qpi.transferShareOwnershipAndPossession(state.mut().mQTRYGOVIdentifier.assetName, state.mut().mQTRYGOVIdentifier.issuer, SELF, SELF, locals.qtryIterator.numberOfOwnedShares(), locals.qtryIterator.owner());
            }
        }
    }

    typedef NoData CleanMemory_input;
    typedef NoData CleanMemory_output;
    struct CleanMemory_locals
    {
        sint64 index;
        uint64 eid;
        id key;
        QtryOrder v;
        sint8 userOption;
        QtryEventInfo qei;
        id uid;
        sint8 winOption;
        RewardTransfer_input rti;
        RewardTransfer_output rto;
        sint32 i;
        bit flag;
        QuotteryLoggerWithData log;
        QuotteryLoggerWithData groupLog;
        uint32 publishResultTick;
        QtryMarketGroupLink marketGroupLink;
        QtryEventGroupInfo eventGroupInfo;
        DepositInfo groupDepositInfo;
    };
    PUBLIC_PROCEDURE_WITH_LOCALS(CleanMemory)
    {
        // Only the system or GO can call this
        if (qpi.invocator() == NULL_ID || qpi.invocator() == state.get().mQtryGov.mOperationId)
        {
            // payout all positions that have final result and then clean all finalized events
            locals.index = NULL_INDEX;
            do {
                locals.index = state.get().mPositionInfo.nextElementIndex(locals.index);
                if (locals.index != NULL_INDEX)
                {
                    locals.key = state.get().mPositionInfo.key(locals.index);
                    locals.v = state.get().mPositionInfo.value(locals.index);
                    locals.eid = locals.key.u64._3 & QUOTTERY_EID_MASK;
                    locals.userOption = locals.key.u64._3 >> 63;
                    state.get().mEventResult.get(locals.eid, locals.winOption);
                    if (locals.winOption != QUOTTERY_RESULT_NOT_SET)
                    {
                        locals.flag = 0;
                        state.get().mEventResultPublishTickTime.get(locals.eid, locals.publishResultTick);
                        if (state.get().mMarketGroupLink.get(locals.eid, locals.marketGroupLink) &&
                            state.get().mEventGroupInfo.get(locals.marketGroupLink.eventGroupId, locals.eventGroupInfo) &&
                            locals.eventGroupInfo.mode == QUOTTERY_EVENT_GROUP_MODE_EXCLUSIVE_ONE)
                        {
                            if (state.get().mEventGroupDisputeInfo.contains(locals.marketGroupLink.eventGroupId))
                            {
                                continue;
                            }
                            if (state.get().mEventGroupDisputeResolved.contains(locals.marketGroupLink.eventGroupId) ||
                                locals.publishResultTick + QUOTTERY_DISPUTE_WINDOW < qpi.tick())
                            {
                                locals.flag = 1;
                            }
                        }
                        else
                        {
                            if (state.get().mDisputeInfo.contains(locals.eid))
                            {
                                continue;
                            }
                            if (locals.publishResultTick + QUOTTERY_DISPUTE_WINDOW < qpi.tick())
                            {
                                locals.flag = 1;
                            }
                        }

                        if (locals.flag)
                        {
                            if (!state.get().mEventFinalFlag.contains(locals.eid))
                            {
                                state.mut().mEventFinalFlag.set(locals.eid, true);
                            }
                            if (locals.userOption == locals.winOption)
                            {
                                locals.rti.amount = smul(state.get().wholeSharePrice, locals.v.amount);
                                locals.rti.eid = locals.eid;
                                locals.rti.receiver = locals.v.entity;
                                locals.rti.needChargeFee = 1;
                                CALL(RewardTransfer, locals.rti, locals.rto);
                                if (!locals.rto.ok)
                                {
                                    state.mut().mEventFinalFlag.set(locals.eid, false); // can't finalize this because failed to give reward to users
                                    continue;
                                }
                            }
                            // remove the position
                            state.mut().mPositionInfo.removeByKey(locals.key);
                        }
                    }
                }
            } while (locals.index != NULL_INDEX);

            locals.index = NULL_INDEX;
            do {
                locals.index = state.get().mEventFinalFlag.nextElementIndex(locals.index);
                if (locals.index != NULL_INDEX)
                {
                    locals.eid = state.get().mEventFinalFlag.key(locals.index);
                    if (!state.get().mEventFinalFlag.value(locals.index)) // flag as false
                    {
                        state.mut().mEventFinalFlag.removeByIndex(locals.index); // clean it for next epoch
                        continue;
                    }
                    locals.log = QuotteryLoggerWithData{ 0, QUOTTERY_ARCHIVE_EVENT, id(0,0, 0, locals.eid), 0 };
                    LOG_INFO(locals.log);

                    if (state.get().mMarketGroupLink.get(locals.eid, locals.marketGroupLink) &&
                        state.get().mEventGroupInfo.get(locals.marketGroupLink.eventGroupId, locals.eventGroupInfo))
                    {
                        if (state.get().mEventGroupGODepositInfo.get(
                            locals.marketGroupLink.eventGroupId,
                            locals.groupDepositInfo))
                        {
                            qpi.transfer(locals.groupDepositInfo.pubkey, locals.groupDepositInfo.amount);
                            state.mut().mEventGroupGODepositInfo.removeByKey(locals.marketGroupLink.eventGroupId);
                        }
                        locals.eventGroupInfo.archivedMarketCount++;
                        if (locals.eventGroupInfo.archivedMarketCount == locals.eventGroupInfo.marketCount)
                        {
                            locals.groupLog = QuotteryLoggerWithData{
                                0,
                                QUOTTERY_ARCHIVED_EVENT_GROUP,
                                id(0, 0, 0, locals.marketGroupLink.eventGroupId),
                                0
                            };
                            LOG_INFO(locals.groupLog);
                            state.mut().mEventGroupResult.removeByKey(locals.marketGroupLink.eventGroupId);
                            state.mut().mEventGroupResultPublishTickTime.removeByKey(locals.marketGroupLink.eventGroupId);
                            state.mut().mEventGroupDisputeInfo.removeByKey(locals.marketGroupLink.eventGroupId);
                            state.mut().mEventGroupDisputeResolver.removeByKey(locals.marketGroupLink.eventGroupId);
                            state.mut().mEventGroupGODepositInfo.removeByKey(locals.marketGroupLink.eventGroupId);
                            state.mut().mEventGroupDisputeResolved.removeByKey(locals.marketGroupLink.eventGroupId);
                            state.mut().mEventGroupMarkets.removeByKey(locals.marketGroupLink.eventGroupId);
                            state.mut().mEventGroupInfo.removeByKey(locals.marketGroupLink.eventGroupId);
                        }
                        else
                        {
                            state.mut().mEventGroupInfo.set(
                                locals.marketGroupLink.eventGroupId,
                                locals.eventGroupInfo
                            );
                        }
                        state.mut().mMarketGroupLink.removeByKey(locals.eid);
                    }

                    // Cleanup the result, freeing the slot in mEventResult
                    state.mut().mEventResult.removeByKey(locals.eid);
                    state.mut().mEventResultPublishTickTime.removeByKey(locals.eid);

                    // Safety cleanup just in case
                    state.mut().mDisputeInfo.removeByKey(locals.eid);
                    state.mut().mGODepositInfo.removeByKey(locals.eid);
                    state.mut().mDisputeResolver.removeByKey(locals.eid);
                    state.mut().mEventInfo.removeByKey(locals.eid);
                    state.mut().mEventFinalFlag.removeByIndex(locals.index);

                    // Clear the active event slot so GetActiveEvent/GetUserPosition don't see stale IDs
                    state.mut().mRecentActiveEvent.set(mod(locals.eid, QUOTTERY_MAX_CONCURRENT_EVENT), NULL_INDEX);
                }
            } while (locals.index != NULL_INDEX);

            state.mut().mEventInfo.cleanup();
            state.mut().mEventFinalFlag.cleanup();
            state.mut().mPositionInfo.cleanup();
            state.mut().mEventResult.cleanup();
            state.mut().mEventResultPublishTickTime.cleanup();
            state.mut().mDisputeInfo.cleanup();
            state.mut().mGODepositInfo.cleanup();
            state.mut().mDisputeResolver.cleanup();
            state.mut().mEventGroupInfo.cleanup();
            state.mut().mEventGroupMarkets.cleanup();
            state.mut().mMarketGroupLink.cleanup();
            state.mut().mEventGroupResult.cleanup();
            state.mut().mEventGroupResultPublishTickTime.cleanup();
            state.mut().mEventGroupDisputeInfo.cleanup();
            state.mut().mEventGroupDisputeResolver.cleanup();
            state.mut().mEventGroupGODepositInfo.cleanup();
            state.mut().mEventGroupDisputeResolved.cleanup();
        }
    }

    BEGIN_EPOCH()
    {
        // TODO: reinitialize after proposal getting passed
        if (qpi.epoch() == 210)
        {
            CALL(Reinit, input, output);
        }
    }

    struct END_EPOCH_locals
    {
        AssetPossessionIterator iter;
        Asset asset;
        uint64 payoutPerShare, payout, total, burn;

        CleanMemory_input cmi;
        CleanMemory_output cmo;
    };
    END_EPOCH_WITH_LOCALS()
    {
        CALL(CleanMemory, locals.cmi, locals.cmo);
        // distribute to QTRY shareholders
        if ((state.get().mShareholdersRevenue - state.get().mDistributedShareholdersRevenue - state.get().mBurnedAmount > 676) && (state.get().mShareholdersRevenue > state.get().mDistributedShareholdersRevenue + state.get().mBurnedAmount))
        {
            // burn fee will be applied on shareholder revenue
            locals.total = state.get().mShareholdersRevenue - state.get().mDistributedShareholdersRevenue - state.get().mBurnedAmount;
            locals.burn = div(smul(locals.total, state.get().mQtryGov.mBurnFee), QUOTTERY_PERCENT_DENOMINATOR);
            if (locals.burn) qpi.burn(locals.burn);

            state.mut().mBurnedAmount += locals.burn;
            locals.total = state.get().mShareholdersRevenue - state.get().mDistributedShareholdersRevenue - state.get().mBurnedAmount;
            locals.payoutPerShare = div(locals.total, (uint64)NUMBER_OF_COMPUTORS);

            locals.asset.assetName = QUOTTERY_CONTRACT_ASSET_NAME;
            locals.asset.issuer = NULL_ID;

            if (locals.payoutPerShare)
            {
                // distribute dividends by tokens, not QUs
                for (locals.iter.begin(locals.asset); !locals.iter.reachedEnd(); locals.iter.next())
                {
                    if (locals.iter.numberOfPossessedShares() > 0)
                    {
                        locals.payout = smul(locals.payoutPerShare, (uint64)locals.iter.numberOfPossessedShares());
                        if (qpi.transferShareOwnershipAndPossession(state.get().mQUSDIdentifier.assetName, state.get().mQUSDIdentifier.issuer, SELF, SELF, locals.payout, locals.iter.possessor()) < 0)
                        {
                            //critical error
                        }
                        else
                        {
                            state.mut().mDistributedShareholdersRevenue += locals.payout;
                        }
                    }
                }
            }
        }
        // distribute to operation team
        if (state.get().mOperationRevenue > state.get().mDistributedOperationRevenue)
        {
            locals.payout = state.get().mOperationRevenue - state.get().mDistributedOperationRevenue;
            if (qpi.transferShareOwnershipAndPossession(state.get().mQUSDIdentifier.assetName, state.get().mQUSDIdentifier.issuer, SELF, SELF, locals.payout, state.get().mQtryGov.mOperationId) < 0)
            {
                //critical error
            }
            else
            {
                state.mut().mDistributedOperationRevenue += locals.payout;
            }
        }

        CALL(FinalizeProposalAndGovernment, input, output);
    }

    /* GOV/PROPOSAL AREA */

    struct ProposalVote_input
    {
        QtryGOV proposed;
    };
    struct ProposalVote_output {};
    struct ProposalVote_locals
    {
        uint64 amountOfShares;
        sint32 i;
        sint32 chosenIndex;
        id publicKey;
        proposalVoter pv;
    };
    PUBLIC_PROCEDURE_WITH_LOCALS(ProposalVote)
    {
        if (state.get().mOperationParams.mAntiSpamAmount)
        {
            if (qpi.invocationReward() < state.get().mOperationParams.mAntiSpamAmount) return;
            if (qpi.invocationReward() > state.get().mOperationParams.mAntiSpamAmount) qpi.transfer(qpi.invocator(), qpi.invocationReward() - state.get().mOperationParams.mAntiSpamAmount);
        }
        locals.amountOfShares = qpi.numberOfShares(state.get().mQTRYGOVIdentifier, { qpi.invocator(), SELF_INDEX }, { qpi.invocator(), SELF_INDEX });
        if (locals.amountOfShares == 0) return;
        // check duplicated publickey
        locals.chosenIndex = -1;
        for (locals.i = 0; locals.i < 676; locals.i++)
        {
            if (state.get().mGovVoters.get(locals.i).publicKey == qpi.invocator())
            {
                locals.chosenIndex = locals.i;
                break;
            }
        }
        if (locals.chosenIndex == -1)
        {
            // get any spot that is not valid:  epoch != qpi.epoch
            for (locals.i = 0; locals.i < 676; locals.i++)
            {
                if (state.get().mGovVoters.get(locals.i).proposedEpoch != qpi.epoch())
                {
                    locals.chosenIndex = locals.i;
                    break;
                }
            }
        }
        if (locals.chosenIndex != -1)
        {
            locals.pv.publicKey = qpi.invocator();
            locals.pv.amountOfShares = locals.amountOfShares;
            locals.pv.proposed = input.proposed;
            locals.pv.proposedEpoch = qpi.epoch();
            state.mut().mGovVoters.set(locals.chosenIndex, locals.pv);
        }
        // update old votes, invalidate the slot if needed
        for (locals.i = 0; locals.i < 676; locals.i++)
        {
            locals.pv = state.get().mGovVoters.get(locals.i);
            if (locals.pv.proposedEpoch == qpi.epoch())
            {
                locals.amountOfShares = qpi.numberOfShares(state.get().mQTRYGOVIdentifier, { locals.pv.publicKey, SELF_INDEX }, { locals.pv.publicKey, SELF_INDEX });
                if (locals.amountOfShares == 0)
                {
                    locals.pv.proposedEpoch = 0;
                    state.mut().mGovVoters.set(locals.i, locals.pv);
                }
            }
        }
    }

    typedef NoData FinalizeProposalAndGovernment_input;
    typedef NoData FinalizeProposalAndGovernment_output;
    struct FinalizeProposalAndGovernment_locals
    {
        sint32 i;
        sint32 currentPoint;

        proposalVoter pv;
        id proposalHash;

        QtryGOV maxVotedProposal;
        sint32 maxVoteCount;

        AssetOwnershipIterator aoi;
        id owner;
        Entity e;
        bit shouldRedistribute;
        sint64 amountOfShares;

        sint32 govCount;
        sint64 govSum;
        sint64 redistributeSum;

        sint64 prev;
        id seed;
        sint32 rd;
    };
    PRIVATE_PROCEDURE_WITH_LOCALS(FinalizeProposalAndGovernment)
    {
        // clear stale vote counts from previous epochs
        state.mut().mVoteMap.reset();
        locals.maxVoteCount = -1;
        for (locals.i = 0; locals.i < 676; locals.i++)
        {
            locals.pv = state.get().mGovVoters.get(locals.i);
            if (locals.pv.proposedEpoch == qpi.epoch())
            {
                locals.pv.amountOfShares = qpi.numberOfShares(state.get().mQTRYGOVIdentifier, { locals.pv.publicKey, SELF_INDEX }, { locals.pv.publicKey, SELF_INDEX });
                locals.proposalHash = qpi.K12(locals.pv.proposed);
                if (!state.get().mVoteMap.get(locals.proposalHash, locals.currentPoint))
                {
                    locals.currentPoint = 0;
                }
                state.mut().mVoteMap.set(locals.proposalHash, locals.currentPoint + sint32(locals.pv.amountOfShares));
                if (locals.maxVoteCount < locals.currentPoint + sint32(locals.pv.amountOfShares))
                {
                    locals.maxVoteCount = locals.currentPoint + sint32(locals.pv.amountOfShares);
                    locals.maxVotedProposal = locals.pv.proposed;
                }
            }
        }
        if (locals.maxVoteCount >= 451)
        {
            state.mut().mQtryGov = locals.maxVotedProposal;
        }
        // reset all vote slots
        for (locals.i = 0; locals.i < 676; locals.i++)
        {
            locals.pv = state.get().mGovVoters.get(locals.i);
            locals.pv.proposedEpoch = 0;
            state.mut().mGovVoters.set(locals.i, locals.pv);
        }
        // checking for GOV holders activities - here we only transfer both ownership and possession at the same time, so we only need to check the ownership
        locals.aoi = AssetOwnershipIterator(state.get().mQTRYGOVIdentifier);
        locals.govCount = 0;
        locals.govSum = 0;
        locals.redistributeSum = qpi.numberOfShares(state.get().mQTRYGOVIdentifier, { SELF, SELF_INDEX }, { SELF, SELF_INDEX });

        while (!locals.aoi.reachedEnd())
        {
            if (locals.aoi.owner() != SELF) // only process if holder isn't QTRY itself
            {
                locals.shouldRedistribute = false;
                if (qpi.getEntity(locals.aoi.owner(), locals.e))
                {
                    if (qpi.tick() - 5000000 >= locals.e.latestOutgoingTransferTick)
                    {
                        // no outgoing last 5000000 ticks, need to move the gov token
                        locals.shouldRedistribute = true;
                    }
                }
                else
                {
                    // this ID doesn't even have 1QU, need to move the gov token
                    locals.shouldRedistribute = true;
                }
                locals.amountOfShares = qpi.numberOfShares(state.get().mQTRYGOVIdentifier, { locals.aoi.owner(), SELF_INDEX }, { locals.aoi.owner(), SELF_INDEX });
                if (locals.shouldRedistribute)
                {
                    // transfer this amount of GOV token to this SC
                    qpi.transferShareOwnershipAndPossession(state.get().mQTRYGOVIdentifier.assetName, state.get().mQTRYGOVIdentifier.issuer, locals.aoi.owner(), locals.aoi.owner(), locals.amountOfShares, SELF);
                    locals.redistributeSum += locals.amountOfShares;
                }
                else
                {
                    state.mut().mGovArray.set(locals.govCount, { locals.aoi.owner() , locals.amountOfShares });
                    locals.govCount++;
                    locals.govSum += locals.amountOfShares;
                }
            }
            locals.aoi.next();
        }
        if (locals.redistributeSum && locals.govCount > 0 && locals.govSum > 0)
        {
            state.mut().mAccumulatedSum.set(0, state.get().mGovArray.get(0).amount);
            for (locals.i = 1; locals.i < locals.govCount; locals.i++)
            {
                locals.prev = state.get().mAccumulatedSum.get(locals.i - 1);
                state.mut().mAccumulatedSum.set(locals.i, locals.prev + state.get().mGovArray.get(locals.i).amount);
            }
            // get the pseudo random from spectrum
            locals.seed = qpi.getPrevSpectrumDigest();
            //randomly airdrop the inactive token to active holders
            while (locals.redistributeSum)
            {
                locals.seed = qpi.K12(locals.seed);
                locals.rd = mod(locals.seed.u32._0, uint32(locals.govSum));
                for (locals.i = 0; locals.i < locals.govCount; locals.i++)
                {
                    if (locals.rd < state.get().mAccumulatedSum.get(locals.i))
                    {
                        // airdrop from SC to active holder
                        locals.owner = state.get().mGovArray.get(locals.i).publicKey;
                        qpi.transferShareOwnershipAndPossession(state.get().mQTRYGOVIdentifier.assetName, state.get().mQTRYGOVIdentifier.issuer, SELF, SELF, 1, locals.owner);
                        locals.redistributeSum--;
                        break;
                    }
                }
            }
        }

    }
    /******END OF GOV/PROPOSAL AREA*****/
public:

    struct GetTopProposals_input
    {
    };
    struct GetTopProposals_output
    {
        struct ProposalInfo
        {
            QtryGOV proposed;
            sint64 totalVotes;
        };
        Array<ProposalInfo, 4> top; // top 3 proposals (index 3 unused)
        sint32 uniqueCount; // total number of distinct proposals this epoch
    };
    struct ProposalEntry
    {
        id hash;
        QtryGOV proposed;
        sint64 votes;
    };

    struct GetTopProposals_locals
    {
        Array<ProposalEntry, 64> entries;
        sint32 entryCount;
        sint32 i, j;
        proposalVoter pv;
        id h;
        bit found;
        sint64 amountOfShares;
        ProposalEntry tmpEntry;
        // for top-3 selection
        sint32 bestIdx;
        sint64 bestVotes;
        Array<sint8, 64> used; // 0=not used, 1=used
        GetTopProposals_output::ProposalInfo pi;
    };

    /**
     * @brief Returns the top 3 governance proposals by total weighted votes in the current epoch.
     */
    PUBLIC_FUNCTION_WITH_LOCALS(GetTopProposals)
    {
        setMemory(output, 0);
        setMemory(locals.entries, 0);
        locals.entryCount = 0;

        // accumulate votes per unique proposal hash
        for (locals.i = 0; locals.i < 676; locals.i++)
        {
            locals.pv = state.get().mGovVoters.get(locals.i);
            if (locals.pv.proposedEpoch != qpi.epoch()) continue;

            locals.amountOfShares = qpi.numberOfShares(state.get().mQTRYGOVIdentifier, { locals.pv.publicKey, SELF_INDEX }, { locals.pv.publicKey, SELF_INDEX });
            if (locals.amountOfShares == 0) continue;

            locals.h = qpi.K12(locals.pv.proposed);
            locals.found = false;
            for (locals.j = 0; locals.j < locals.entryCount; locals.j++)
            {
                if (locals.entries.get(locals.j).hash == locals.h)
                {
                    locals.found = true;
                    locals.tmpEntry = locals.entries.get(locals.j);
                    locals.tmpEntry.votes += locals.amountOfShares;
                    locals.entries.set(locals.j, locals.tmpEntry);
                    break;
                }
            }
            if (!locals.found && locals.entryCount < 64)
            {
                locals.tmpEntry.hash = locals.h;
                locals.tmpEntry.proposed = locals.pv.proposed;
                locals.tmpEntry.votes = locals.amountOfShares;
                locals.entries.set(locals.entryCount, locals.tmpEntry);
                locals.entryCount++;
            }
        }
        output.uniqueCount = locals.entryCount;

        // pick top 3
        setMemory(locals.used, 0);
        for (locals.i = 0; locals.i < 3 && locals.i < locals.entryCount; locals.i++)
        {
            locals.bestIdx = -1;
            locals.bestVotes = -1;
            for (locals.j = 0; locals.j < locals.entryCount; locals.j++)
            {
                if (!locals.used.get(locals.j) && locals.entries.get(locals.j).votes > locals.bestVotes)
                {
                    locals.bestVotes = locals.entries.get(locals.j).votes;
                    locals.bestIdx = locals.j;
                }
            }
            if (locals.bestIdx != -1)
            {
                locals.pi.proposed = locals.entries.get(locals.bestIdx).proposed;
                locals.pi.totalVotes = locals.entries.get(locals.bestIdx).votes;
                output.top.set(locals.i, locals.pi);
                locals.used.set(locals.bestIdx, true);
            }
        }
    }

    struct GetApprovedAmount_input
    {
        id pk;
    };
    struct GetApprovedAmount_output
    {
        uint64 amount;
    };
    PUBLIC_FUNCTION(GetApprovedAmount)
    {
        output.amount = qpi.numberOfShares(
            state.get().mQUSDIdentifier,
            { input.pk, SELF_INDEX },
            { input.pk, SELF_INDEX }
        );
    }

    struct TransferQUSD_input
    {
        id receiver;
        sint64 amount;
    };
    struct TransferQUSD_output
    {
        uint64 amount;
    };
    PUBLIC_PROCEDURE(TransferQUSD) // that is managed by this SC
    {
        if (input.amount <= 0) { output.amount = -1; return; }
        if (qpi.transferShareOwnershipAndPossession(state.get().mQUSDIdentifier.assetName, state.get().mQUSDIdentifier.issuer, qpi.invocator(), qpi.invocator(), input.amount, input.receiver) < 0)
        {
            output.amount = -1;
        }
        else
        {
            output.amount = input.amount;
        }
    }

    struct TransferQTRYGOV_input
    {
        id receiver;
        sint64 amount;
    };
    struct TransferQTRYGOV_output
    {
        uint64 amount;
    };
    PUBLIC_PROCEDURE(TransferQTRYGOV) // that is managed by this SC
    {
        if (input.amount <= 0) { output.amount = -1; return; }
        if (qpi.transferShareOwnershipAndPossession(state.get().mQTRYGOVIdentifier.assetName, state.get().mQTRYGOVIdentifier.issuer, qpi.invocator(), qpi.invocator(), input.amount, input.receiver) < 0)
        {
            output.amount = -1;
        }
        else
        {
            output.amount = input.amount;
        }
    }

    // copy from QSWAP: use this to transfer management right back to wherever SC users want

    struct TransferShareManagementRights_input
    {
        Asset asset;
        sint64 numberOfShares;
        uint32 newManagingContractIndex;
    };
    struct TransferShareManagementRights_output
    {
        sint64 transferredNumberOfShares;
    };

    struct TransferShareManagementRights_locals
    {
        sint64 result;
        sint64 reward;
        sint64 refundAmount;
        sint64 requiredFee;
        bit success;
    };

    PUBLIC_PROCEDURE_WITH_LOCALS(TransferShareManagementRights)
    {
        // only allow to transfer mgmt right from mQUSDIdentifier
        if (input.asset.assetName != state.get().mQUSDIdentifier.assetName || input.asset.issuer != state.get().mQUSDIdentifier.issuer)
        {
            return;
        }
        locals.reward = qpi.invocationReward();
        locals.refundAmount = locals.reward;

        output.transferredNumberOfShares = 0;

        locals.success = false;

        if (qpi.numberOfPossessedShares(
            input.asset.assetName,
            input.asset.issuer,
            qpi.invocator(),
            qpi.invocator(),
            SELF_INDEX,
            SELF_INDEX) >= input.numberOfShares)
        {
            locals.result = qpi.releaseShares(
                input.asset,
                qpi.invocator(),
                qpi.invocator(),
                input.numberOfShares,
                input.newManagingContractIndex,
                input.newManagingContractIndex,
                locals.reward
            );

            if (locals.result != INVALID_AMOUNT && locals.result >= 0)
            {
                locals.success = true;
                locals.refundAmount = locals.reward - locals.result;
            }
        }

        if (locals.success)
        {
            output.transferredNumberOfShares = input.numberOfShares;
        }

        if (locals.refundAmount > 0)
        {
            qpi.transfer(qpi.invocator(), locals.refundAmount);
        }
    }

    PRE_ACQUIRE_SHARES()
    {
        output.allowTransfer = true;
    }
};
