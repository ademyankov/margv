//
// Minimalistic command line argument parser
//
// Copyright(c) 2022 Alex Demyankov <alex.demyankov@gmail.com>
// All rights reserved.
//
// Licensed under the MIT license; A copy of the license that can be
// found in the LICENSE file.
//

#pragma once

#include <map>
#include <string>

namespace margv {

    namespace detail {
        template <typename T> T get(bool, const std::string&, const std::string&) {}
        template <> inline bool get<bool>(bool is, const std::string&, const std::string&) { return is; }
        template <> inline std::string get<std::string>(bool is, const std::string& got, const std::string& def) { return is ? got : def; }
        template <> inline int get<int>(bool is, const std::string& got, const std::string& def) {
            return (int)strtoul(detail::get<std::string>(is, got, def).c_str(), NULL, 0);
        }
    }

    class argv {
    public:
        enum class ArgValue { NotRequired, Required, Optional };

    public:
        argv() = default;
        ~argv() = default;

        int parse(int argc, char** argv) {
            int exclusive{};
            for (int i = 1; i < argc; ++i) {
                if (argv[i][0] != '-') continue;

                auto it = kvm_.find(&argv[i][1]);
                if (it == kvm_.end()) continue;

                // mark as present
                std::get<0>(it->second) = true;

                if (std::get<4>(it->second)) ++exclusive;
                if (std::get<3>(it->second) == ArgValue::NotRequired) continue;
                if (std::get<3>(it->second) == ArgValue::Required) {
                    if (++i >= argc || argv[i][0] == '-') return -1;
                } else if (std::get<3>(it->second) == ArgValue::Optional) {
                    if (i + 1 >= argc || argv[i + 1][0] == '-') continue;
                    ++i;
                } else return -1;

                // store the switch's parameter
                std::get<1>(it->second) = argv[i];
            }
            return exclusive ? 0 : -1;
        }

        // Add an exclusive switch with an optional parameter;
        // Exclusive switch means that at least one exclusive switch is
        // required to be present in the command line arguments list
        int add_optional(const std::string& arg) {
            return add(arg, "", ArgValue::Optional, true);
        }

        // Add an exclusive switch with a required parameter
        int add_required(const std::string& arg) {
            return add(arg, "", ArgValue::Required, true);
        }

        // Add an optional true switch
        int add_switch(const std::string& arg) {
            return add(arg, "", ArgValue::NotRequired, false);
        }

        int add(const std::string& arg, const std::string& default_value, ArgValue param = ArgValue::NotRequired, bool exclusive = false) {
            if (kvm_.find(arg) != kvm_.end()) return -1;
            kvm_[arg] = std::make_tuple(false, std::string(""), default_value, param, exclusive);
            return 0;
        }

        int add(const char* arg, const char* default_value) {
            return add(arg, default_value, ArgValue::Required, false);
        }

        int add(const char* arg, bool exclusive) {
            return add(arg, "", ArgValue::NotRequired, exclusive);
        }

        int add(const char* arg, ArgValue param, bool exclusive) {
            return add(arg, "", param, exclusive);
        }

        template <typename T> T get(const std::string& arg) {
            if (kvm_.find(arg) == kvm_.end()) return detail::get<T>(false, "", "");
            auto it = kvm_[arg];
            return detail::get<T>(std::get<0>(it), std::get<1>(it), std::get<2>(it));
        }

    private:
        //               present    -name       default     param  exclusive
        typedef std::tuple<bool, std::string, std::string, ArgValue, bool> ex_;
        std::map<std::string, ex_> kvm_;
    };

}
