// Copyright 2019-2022 CERN and copyright holders of ALICE O2.
// See https://alice-o2.web.cern.ch/copyright for details of the copyright holders.
// All rights not expressly granted are reserved.
//
// This software is distributed under the terms of the GNU General Public
// License v3 (GPL Version 3), copied verbatim in the file "COPYING".
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

/// \author Gvozden Nešković, Frankfurt Institute for Advanced Studies and Goethe University Frankfurt

#include "ReadoutDevice.h"

#include <fairmq/ProgOptions.h>

#include "runFairMQDevice.h"

namespace bpo = boost::program_options;
template class std::basic_string<char, std::char_traits<char>, std::allocator<char> >; // Workaround for bug in CC7 devtoolset7

void addCustomOptions(bpo::options_description& options)
{
  options.add_options()(
    o2::DataDistribution::ReadoutDevice::OptionKeyOutputChannelName,
    bpo::value<std::string>()->default_value("readout"),
    "Name of the readout output channel")(
    o2::DataDistribution::ReadoutDevice::OptionKeyReadoutDataRegionSize,
    bpo::value<std::size_t>()->default_value(1ULL << 30 /* 1GiB */),
    "Size of the data shm segment")(
    o2::DataDistribution::ReadoutDevice::OptionKeyLinkIdOffset,
    bpo::value<size_t>()->default_value(0),
    "Offset of CRU equipment ID. Starts at 0. (offset + #)")(
    o2::DataDistribution::ReadoutDevice::OptionKeyCruSuperpageSize,
    bpo::value<size_t>()->default_value(2ULL << 20 /* 2MiB */),
    "CRU DMA superpage size")(
    o2::DataDistribution::ReadoutDevice::OptionKeyOrbitsInTf,
    bpo::value<size_t>()->default_value(128ULL),
    "Number of orbits in TimeFrame")(
    o2::DataDistribution::ReadoutDevice::OptionKeyCruLinkCount,
    bpo::value<uint64_t>()->default_value(2),
    "Number of CRU equipments to emulate (links, user logics, ...).")(
    o2::DataDistribution::ReadoutDevice::OptionKeyCruLinkBitsPerS,
    bpo::value<double>()->default_value(1000000000),
    "Input throughput per link (bits per second).");
}

FairMQDevicePtr getDevice(const fair::mq::ProgOptions& /*config*/)
{
  return new o2::DataDistribution::ReadoutDevice();
}
