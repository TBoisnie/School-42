import React, { useMemo } from 'react';
import { useTranslation } from 'react-i18next';
import FixedInput from '../../../../common/FixedInput';

interface Props {
    defaultValue: string;
}

const LastName: React.FC<Props> = ({
    defaultValue,
}) => {

    // 5. useCustom
    const { t } = useTranslation();

    // 6. useCallback / useMemo
    const labelTranslation = useMemo(() => t('profile.input.lastname'), [t]);

    return (
        <FixedInput
            name="lastname"
            label={labelTranslation}
            defaultValue={defaultValue}
        />
    );
};

export default LastName;
