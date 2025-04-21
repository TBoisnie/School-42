import React, { useMemo } from 'react';
import { useTranslation } from 'react-i18next';
import FixedInput from '../../../../common/FixedInput';

interface Props {
    defaultValue: string;
}

const FirstName: React.FC<Props> = ({
    defaultValue,
}) => {

    const { t } = useTranslation();

    const labelTranslation = useMemo(() => t('profile.input.firstname'), [t]);

    return (
        <FixedInput
            name="firstname"
            label={labelTranslation}
            defaultValue={defaultValue}
        />
    );
};

export default FirstName;
