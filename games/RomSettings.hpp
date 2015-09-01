/* *****************************************************************************
 * Xitari
 *
 * Copyright 2014 Google Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 * *****************************************************************************
 * A.L.E (Arcade Learning Environment)
 * Copyright (c) 2009-2013 by Yavar Naddaf, Joel Veness, Marc G. Bellemare and 
 *   the Reinforcement Learning and Artificial Intelligence Laboratory
 * Released under the GNU General Public License; see License.txt for details. 
 *
 * Based on: Stella  --  "An Atari 2600 VCS Emulator"
 * Copyright (c) 1995-2007 by Bradford W. Mott and the Stella team
 *
 * *****************************************************************************
 *
 * RomSettings.hpp
 *
 * The interface to describe games as RL environments. It provides terminal and
 *  reward information.
 * *****************************************************************************
 */
#ifndef __ROMSETTINGS_HPP__
#define __ROMSETTINGS_HPP__

#include "../common/Constants.h"
#include "../emucore/Serializer.hxx"
#include "../emucore/Deserializer.hxx"
#include <iostream>
namespace ale {

class System;


// rom support interface
struct RomSettings {

    virtual ~RomSettings() {}

    // reset
    virtual void reset() = 0;

    // is end of game
    virtual bool isTerminal() const = 0;

    // get the most recently observed reward
    virtual reward_t getReward() const = 0;
    //
    virtual reward_t getRewardB () const {return 0;};

    virtual double getSideBouncing () const {return 0;};
    virtual bool getWallBouncing () const {return false;};
    virtual bool getCrash () const {return false;};
    virtual bool getServing () const {return false;};
    virtual int getPoints () const {return 0;};
    // the rom-name
    virtual const char *rom() const = 0;

    // create a new instance of the rom
    virtual RomSettings *clone() const = 0;

    // is an action part of the minimal set?
    virtual bool isMinimal(const Action &a) const = 0;

   // is an action part of the minimal set for player 2?
    virtual bool isMinimalB(const Action &a) const {return 0;};

    // process the latest information from ALE
    virtual void step(const System &system) = 0;

    // saves the state of the rom settings
    virtual void saveState(Serializer & ser) = 0;
    
    // loads the state of the rom settings
    virtual void loadState(Deserializer & ser) = 0;

    // is an action legal (default: yes)
    virtual bool isLegal(const Action &a) const;
    
     // is an action legal for player 2?
    virtual bool isLegalB(const Action &a) const;

    // Minimum possible instantaneous reward. 
    virtual reward_t minReward() const { return -65536; }

    // Maximum possible instantaneous reward.
    virtual reward_t maxReward() const { return 65536; }

    // Remaining lives.
    virtual int lives() const { return isTerminal() ? 0 : 1; }
    // Remaining lives B.
    virtual int livesB() const { return isTerminal() ? 0 : 1; }

    // Returns a restricted (minimal) set of actions. If not overriden, this is all actions.
    virtual ActionVect &getMinimalActionSet();
    // Returns a restricted (minimal) set of actions for player 2.
    virtual ActionVect &getMinimalActionSetB();

    // Returns the set of all legal actions
    ActionVect &getAllActions();
    // Returns the set of all legal actions
    ActionVect &getAllActionsB();

    // Returns a list of actions that are required to start the game.
    // By default this is an empty list.
    virtual ActionVect getStartingActions();

    // Returns whether we should swap the left and right player ports.
    virtual bool swapPorts() const { return false; }

    // Maximum number of frames for the environment before termination
    virtual int maxFrames() const { return 8*60*60*60; }

    protected:
      ActionVect actions;
      ActionVect actionsB;
      ActionVect all_actions;
      ActionVect all_actionsB;
};

} // namespace ale

#endif // __ROMSETTINGS_HPP__


