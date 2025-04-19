# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/04 15:46:15 by tboisnie          #+#    #+#              #
#    Updated: 2019/12/11 22:54:45 by tboisnie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FROM debian:buster-slim

# MISC
LABEL maintainer="BOISNIER Thomas <tboisnie@student.42.fr>"

# COPY REQUIREMENTS
COPY ./localhost		/tmp/localhost
COPY ./install.sh		/tmp/install.sh

# INSTALL
CMD ["bash", "/tmp/install.sh"]
